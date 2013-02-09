#!/bin/sh
# Rildo Pragana -- Recife, 2001
#\
exec wish "$0" "$@"

# change the folowing to your cobol compile arguments
set gdb(cobol_args) "-P -D -I." 
# set your compiler path here
set gdb(compiler_path) "../../compiler"
# set list of lval casts to be chosen from
set gdb(cast_list) {
    {struct sym *}
	{int}
    {struct lit *}
    {unsigned long}
    {char *}
    {condition}
	{struct vref *}
    {struct refmod *}
    {struct string_from *}
    {struct unstring_delimited *}
    {struct unstring_destinations *}
    {struct tallying_list *}
    {struct tallying_for_list *}
    {struct replacing_list *}
    {struct replacing_by_list *}
    {struct inspect_before_after *}
    {struct scr_info *}
    {struct perf_info *}
    {struct perform_info *}
 	{struct sortfile_node *}
	{struct selsubject *}
	{struct list *}
	{struct coord_pair}
}

#####################################################
### please, don't touch anything below
set gdb(sourcefile) "tdb03.cob"
set gdb(asmfile) ""
set gdb(fd) -1
set history {step}
tcl_wordBreakAfter "Rildo Pragana" 0 ;# force loading package first
set tcl_wordchars {[a-zA-Z0-9_-]} 
set tcl_nonwordchars {[^a-zA-Z0-9_-]}

### communication with gdb
proc gdbReceive {} {
	global gdb
	if {$gdb(ready)} {
		set gdb(answer) ""
		set gdb(ready) 0
	}
	set line [gets $gdb(fd)] 
	if {[string compare $line **READY**]} {
		append gdb(answer) $line\n
	} else {
		incr gdb(ready)
	}
	#puts "answer: $gdb(answer)"
}

proc sendgdb {cmd {wait 1}} {
	global gdb
	set gdb(answer) ""
	set gdb(ready) 0
	puts $gdb(fd) $cmd
	if {$wait} {
		while {!$gdb(ready)} {
			update
		}
	}
}

proc ask_load_first {} {
	tk_messageBox -message "Please load a source file first!"
}

proc load {} {
	global gdb win
	set gdb(sourcefile) [tk_getOpenFile \
		-filetypes {{{Cobol source} .cob} {{All files} *}} \
		-defaultextension cob]
	if {$gdb(sourcefile) == ""} {
		return
	}
	wm title . "Compiling $gdb(sourcefile)"
	# locate breakpoints and create a list
	set bkps {}
	set lines [split [exec grep -n {yystate[ \t]*=[^=]} \
			[file join $gdb(compiler_path) htcobol.c]] \n]
	foreach line $lines {
		regexp {([0-9]+):.*} $line match bkp
		lappend bkps $bkp
	}
	#puts $bkps
	# prepare connection to gdb task
	set gdb(asmfile) [file rootname $gdb(sourcefile)].s	
	set gdb(asmpos) 0
	set gdb(tok) ""
	set gdb(state) 0 
	set gdb(lineno) 1
	set gdb(ready) 1
	set gdb(fd) [open "|gdb -nx -q 2>@stdout" w+]
	fconfigure $gdb(fd) -blocking 0 -buffering line 
	fileevent $gdb(fd) readable gdbReceive
	sendgdb "set prompt **READY**\\n" 0
	sendgdb "set confirm off" 1
	sendgdb "set width 0" 1
	sendgdb "file [file join $gdb(compiler_path) htcobol]" 1
	sendgdb "set args $gdb(cobol_args) [file tail $gdb(sourcefile)]" 1
	foreach bkp $bkps {
		sendgdb "b htcobol.c:$bkp" 1
	}
	sendgdb "r" 1
	# load cobol source modified by the preprocessor
	sendgdb "c" 1
	$win(source) delete 0.0 end
	set inputname ""
	sendgdb "p inputname" 1 	
	regexp {[^\"]*\"([^\"]*)\"} $gdb(answer) match inputname
	set f [open $inputname r]
	set n 0
	while {![eof $f]} {
		$win(source) insert end "[format %04d [incr n]]: [gets $f]\n"
	}
	close $f
	# setup parser display variables
	sendgdb "display real_lineno" 1
	#sendgdb "display *yyssp" 1
	sendgdb "display yystate" 1
	sendgdb "display yytext" 1
	.status.loaded config -bg red
}

### parse y.output file

proc parse_yacc_states {fname cname} {
	global state action
	set f [open $fname r]
	while {![eof $f]} {
		gets $f line
		if {[regexp {state[ \t]*([0-9]+)$} $line match st]} {
			set state($st) ""
			gets $f line
			while {[regexp {.*\(([0-9]+)\)$} $line match rule]} {
				append state($st) [string trimleft $line]\n
				gets $f line
			}
		} elseif {[regexp {[ \t]*([0-9]+)[ \t]*\$\$([0-9]+).*} $line \
				match rulen actn]} {
			set arule($rulen) $actn
		}
	}
	close $f
	set f [open $cname r]
	while {![eof $f]} {
		gets $f line
		if {[regexp {^case[ \t]*([0-9]+):.*} $line match rulen]} {
			if {[info exists arule($rulen)]} {
				set ix $arule($rulen)
				gets $f line
				gets $f line ;# skip line with "#line" declaration
				while {![string match "break;" $line]} {
					append action($ix) $line\n
					gets $f line
				}
			}
		}
	}
	close $f
}

proc next {{update 1}} {
	global gdb win state
	sendgdb "c"
	if {![regexp {.*real_lineno *= *([0-9]+).*} $gdb(answer) \
		match gdb(lineno)]} {
			.status.loaded config -bg blue 
			return
	}	
	if {$update} {
		#regexp {.*yyssp *= *([0-9]+).*} $gdb(answer) match gdb(state)
		regexp {.*yystate *= *([0-9]+).*} $gdb(answer) match gdb(state)
		regexp {.*yytext *= *[^\"]*\"([^\n]*)\n.*} $gdb(answer) match gdb(tok)
		set gdb(tok) [string range $gdb(tok) 0 end-1]
		$win(state) delete 0.0 end
		#$win(state) insert end $state($gdb(state))
		show_state $win(state) $state($gdb(state))
		sendgdb "p ftell(o_src)"
		regexp {.*= *([0-9]+)} $gdb(answer) match pos
		if {![info exists pos]} {
			#.status.loaded config -bg blue 
			return -1
		}
		if {$pos != $gdb(asmpos)} {
			sendgdb "p fflush(o_src)"
			set f [open $gdb(asmfile) r]
			seek $f $gdb(asmpos) start
			$win(asm) tag remove last 0.0 end
			while {![eof $f]} {
				gets $f line
				$win(asm) insert end $line\n last
			}
			close $f
			$win(asm) see end
			set gdb(asmpos) $pos
		}
	}
	$win(source) tag remove line 0.0 end
	set n $gdb(lineno)
	$win(source) tag add line $n.0 $n.end 	
	$win(source) see [expr $n+3].0
	$win(source) see $n.0
	if {$update} {
		show_lvals 0
	}
	return $gdb(state)
}

proc show_state {w st} {
	global action
	set i [string first " . " $st]
	if {$i > 0} {
		$w insert end [string range $st 0 [expr $i]] normal \
			" " highlight [string range $st [expr $i+2] end] normal
	} else {
		$w insert end $st
	}
	# show mid-of-rule actions found
	while {[regexp {\$\$([0-9]+)[ \t]*:(.*)} $st match actn st]} {
		if {[info exists action($actn)]} {
			$w insert end "\$\$$actn: $action($actn)\n" action
		}
	}
}

proc run {} {
	global gdb
	if {$gdb(fd) < 0} {
		ask_load_first 
		return
	}
	set until [.ctrl.until get]
	if {$until != ""} {
		while {$gdb(lineno) < $until} {
			next 0
		}
		next
		set gdb(until) ""
	} else {
		#set state $gdb(state)
		#while {$state == $gdb(state)} {
		#	if {[next] < 0} break
		#}
		next
	}
}

proc gdbsh {} {
	global gdb
	if {![winfo exists .gdb]} {
		toplevel .gdb
		pack [frame .gdb.t] -fill both -expand 1
		pack [frame .gdb.b] -fill x
		pack \
			[button .gdb.b.close -text close -command {wm withdraw .gdb}] \
			[label .gdb.b.lb -text \
				"Press right mouse button to get cmd history or \
				use the keys <up>,<down>"] \
			-side left
		set t [create_text .gdb.t 18] 
		set gdb(shprompt) "gdb> "
		$t tag config answer -foreground navy 
		$t insert insert $gdb(shprompt) 
		$t mark set limit insert
		$t mark gravity limit left
		focus $t
		bind gdb <Up> { gdbHistory %W 1 ; break }
		bind gdb <Down> { gdbHistory %W 0 ; break }
		bind gdb <Return> { gdbEval %W ; break }
		bind gdb <Any-Key> {
				if [%W compare insert < limit] {
						%W mark set insert end
				}
		}
		bind gdb <3> { popupHistory %W %X %Y ; break }
		bindtags $t [list gdb Text $t all]
	} else {
		wm deiconify .gdb
	}
}

proc popupHistory { t x y } {
	global gdb history
	if {![winfo exists .popup]} {
		toplevel .popup
		wm transient .popup .gdb
		wm geometry .popup +$x+$y
		pack [button .popup.cancel -text cancel -command {
				wm withdraw .popup }] -side bottom
		pack [set lb \
			[listbox .popup.lb -yscrollcommand {.popup.sb set}]] \
			[scrollbar .popup.sb -orient vertical -command {.popup.lb yview}] \
			-side left -fill y
		bindtags $lb [list Listbox all $lb]
		bind $lb <1> [list executeHistory $t %W]	
	}	
	.popup.lb delete 0 end
	foreach it $history {
		.popup.lb insert 0 $it
	}
	wm deiconify .popup
	wm geometry .popup +$x+$y
}

proc executeHistory {t lb} {
	global history
	$t delete limit end
	$t insert insert [string trimright [$lb get [$lb curselection]]]
	wm withdraw .popup
	gdbEval $t
}

proc gdbHistory { t up } {
	global gdb history
	if {$up} {
		$t delete limit end
		$t insert insert [lindex $history end]
		set history [concat \
			[lrange $history end end] [lrange $history 0 end-1]]
	} else {
		$t delete limit end
		$t insert insert [lindex $history 0]
		set history [concat \
			[lrange $history 1 end] [lrange $history 0 0]]
	}
}

proc gdbEval { t } {
	global gdb history
	set command [string trimright [$t get limit end]]
	if {$command != ""} {
		lappend history $command
		set history [lrange $history 0 100]
	}
	$t insert insert \n
	sendgdb $command
	if {[string length $gdb(answer)] > 0} {
		$t insert insert $gdb(answer)\n answer
	}
	$t insert insert $gdb(shprompt)
	$t see insert
	$t mark set limit insert
}

proc show_lvals {{update 1}} {
	global gdb history
	if {$gdb(fd) < 0} {
		ask_load_first
		return
	}
	if {$update && ![winfo exists .lvals]} {
		toplevel .lvals
		grid \
			[listbox .lvals.lb1 -yscrollcommand {.lvals.sb1 set}] \
			[scrollbar .lvals.sb1 -orient vertical \
				-command {.lvals.lb1 yview}] \
			[listbox .lvals.lb -yscrollcommand {.lvals.sb set}] \
			[scrollbar .lvals.sb -orient vertical -command {.lvals.lb yview}] \
			[text .lvals.t -width 60 -height 12 -takefocus 0] \
			-stick nsew
		grid [button .lvals.close -text close -command {
				wm withdraw .lvals }] -stick w
		foreach cast $gdb(cast_list) {
			.lvals.lb1 insert end $cast
		}
		foreach lb {.lvals.lb .lvals.lb1} {
			bindtags $lb [list Listbox all $lb]
			bind $lb <1> [list showLval $lb]
		}
	}
	if {![winfo exists .lvals] || !$update && ![winfo ismapped .lvals]} {
		return
	}
	#wm withdraw .lvals
	.lvals.lb delete 0 end
	sendgdb "p &yyvs"
	regexp {.*(0x[0-9xa-fA-F]+).*} $gdb(answer) match start
	sendgdb "p yyvsp"
	regexp {,*(0x[0-9a-fA-F]+).*} $gdb(answer) match end
	set values {}
	for {set i [expr ($end-$start)/8]} {$i >= 0} {incr i -1} {
		sendgdb "p yyvs\[$i]"
		regexp { ival = ([0-9a-fA-Fx]+).*} $gdb(answer) match lval
		lappend values 0x[format %x $lval]
	}
	eval .lvals.lb insert 0 $values
	wm deiconify .lvals
}

proc showLval {lb} {
	global gdb
	$lb activate [$lb curselection]
	if {[.lvals.lb get active] == {} ||
		[.lvals.lb1 get active] == {}} { return }
	set cast [.lvals.lb1 get active]
	set var [.lvals.lb get active]
	if {[string index $cast end] == "*"} {
		sendgdb "p *($cast)	$var"
	} else {
		sendgdb "p ($cast) $var"
	}
	set result [string range $gdb(answer) \
		[expr [string first = $gdb(answer)]+1] end]
	set result [string trimleft $result " \t\n\{"]
	set result [string trimright $result " \t\n\}"]
	.lvals.t delete 0.0 end
	foreach item [split $result ,] {
		foreach {lhs rhs} [split [string trim $item] =] {}
		.lvals.t insert end $lhs\t$rhs\n
	}
}

proc show_value {var} {
	global gdb
	if {[string first "-" $var]} {
		sendgdb "p '$var'"
	} else {
		sendgdb "p $var"
	}
	tk_messageBox -type ok -message "Inspect $var\n$gdb(answer)"
}

proc create_text {w {height 10} {width 80}} {
	text $w.t -width $width -height $height \
		-yscrollcommand "$w.sv set" -xscrollcommand "$w.sh set"
	scrollbar $w.sv -orient vertical -command "$w.t yview"
	scrollbar $w.sh -orient horizontal -command "$w.t xview"
	pack $w.sh -side bottom -fill x
	pack $w.sv -side right -fill y
	pack $w.t -side left -fill both -expand 1
	bindtags $w.t [list Text $w.t . all]
	bind $w.t <Double-1> {show_value [%W get sel.first sel.last]}
	bind $w.t <Control-1> {show_value [%W get sel.first sel.last]}
	return $w.t
}

set w [frame .ctrl]
#	[label $w.lab1 -text Source:] \
#	[entry $w.sourcef -width 20 -textvariable gdb(sourcefile)] \
#
pack \
	[button $w.load -command load -text load] \
	[button $w.run -command run -text "run until"] \
	[entry $w.until -width 4 -textvariable gdb(until)] \
	[button $w.gdbsh -command gdbsh -text gdbsh] \
	[button $w.lval -command show_lvals -text "lval stack"] \
	[button $w.exit -command exit -text exit] \
	-side left -pady 10 -padx 5
set w [frame .status]
pack \
	[label $w.lab2 -text Line:] \
	[label $w.lab3 -relief sunken -bd 2 -width 4 -textvariable gdb(lineno)] \
	[label $w.lab4 -text State:] \
	[label $w.lab5 -relief sunken -bd 2 -width 4 -textvariable gdb(state)] \
	[label $w.lab6 -text Token:] \
	[label $w.lab7 -relief sunken -bd 2 -width 20 -textvariable gdb(tok)] \
	[frame $w.loaded -relief sunken -bd 2 -width 10 -height 10] \
	-side left -pady 10 -padx 5

set win(source) [create_text [frame .f1]]
set win(state) [create_text [frame .f2] 8]
set win(asm) [create_text [frame .f3] 18]
pack .ctrl .status .f2 .f1 .f3 -fill both
$win(state) tag config highlight -background red 
$win(state) tag config action -foreground darkgreen 
$win(state) tag config normal -foreground black
$win(asm) tag config last -foreground maroon
$win(source) tag config line -background navy -foreground yellow

parse_yacc_states [file join $gdb(compiler_path) y.output] \
	[file join $gdb(compiler_path) htcobol.c]

bind all <Control-r> run
bind all <Control-c> exit
wm title .  "NO COBOL SOURCE LOADED"

