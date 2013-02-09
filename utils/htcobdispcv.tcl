#!/bin/sh
#
# Utility to convert Cobol display statements from the 
# "DISPLAY (X, Y) A B C ..."  format to 
# the format "DISPLAY A B C ... LINE X POSITION Y"
# 
# * keeps the period after the statement
# * requires that "display" and "(X, Y)" be at the same line
# * case insensitive
# * only variables declared are checked (no copybooks), so please
# 	substitute copy statements with the preprocessor first.
#
# Recife, Brazil 2001 -- Rildo Pragana <rpragana@acm.org>
# 
# usage: ./htcobdispcv.tcl < original.cob > converted.cob
# \
exec tclsh "$0" "$@"

set div none
set varlist {}
set redisp {^(display|accept)[ \t]*\([ \t]*([0-9]+)[ \t]*,[ \t]*([0-9]+)[ \t]*\)(.*)}
set reword {^(([a-zA-Z][a-zA-Z0-9-]*)([ \t]*\([^\)]*\))*)(.*)}
set line ""

while {![eof stdin]} {
	if {$line == ""} { 
		gets stdin line
	}
	if {[regexp -nocase {data[ \t]*division} $line]} {
		puts "* begin data division"
		set div data
	}
	if {[regexp -nocase {procedure[ \t]*division} $line]} {
		puts "* begin procedure division"
		set div procedure
		puts "* VARLIST: $varlist"
	}
	if {$div == "data"} {
		if {[regexp {^[ \t]*[0-9]+[ \t]*([a-zA-Z][a-zA-Z0-9-]*)} $line m var]} {
			lappend varlist $var
		}
	}
	if {$div == "procedure"} {
		set line [string trim $line]
		if {[regexp -nocase $redisp $line m cmd lin pos tail]} {
			puts "*** converted [string toupper $cmd] statement"
			puts "\t$cmd "
			set line $tail
			set add_period 0
			while {1} {
				if {$line == ""} {
					gets stdin line
				}
				set line [string trim $line]
				if {[regexp $reword $line m xtok tok stok tail]} {
					if {([lsearch -exact $varlist $tok] < 0) && \
						![regexp -nocase {^(in|of)} $tok]} {
						if {$add_period} {
							puts "\t\t\tline $lin position $pos\n\t."
						} else {
							puts "\t\t\tline $lin position $pos"
						}
						break
					} else {
						#puts "***** tok: $tok // tail: $tail"
						puts "\t\t${xtok}"
						set line $tail
					}
				} elseif {[regexp {^(\"[^\"]*\")(.*)} \
					$line m tok tail]} {
					puts "\t\t${tok}"
					set line $tail
				} elseif {[regexp {^([0-9.,]+)(.*)} \
					$line m tok tail]} {
					if {($tok != ",") && ($tok != ".")} {
						puts "\t\t${tok}"
					} elseif {$tok == "."} {
						set add_period 1
					}
					set line $tail
				} else {
					puts "\t\t\tline $lin position $pos"
					break
				}
			}
		} else {
			puts $line
			set line ""
		}
	} else {
		puts $line
		set line ""
	}
}

