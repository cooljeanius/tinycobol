# this script receives "data_block" with the (group) value
# of the cobol variable and returns "result"

## visual tcl leaves the main window iconified, so let's show it
wm deiconify .

###### put in this list varname, size pairs

set cobol_fields {
	title 		20
	url		 	50
} 

grid [label .msg -text \
	"Use <Tab> to navigate, <Return> (or click button) \n\
to return to main program."] -columnspan 2

grid \
	[label .lab1 -text "Title:"] \
	[entry .e1 -width 20 -textvariable title] -padx 5 -pady 5 -sticky nsw
grid \
	[label .lab2 -text "URL:"] \
	[entry .e2 -width 50 -textvariable url] -padx 5 -pady 5 -sticky nsw

grid [button .ready -text Enter -command do_exit] \
	-columnspan 2 -pady 20 -sticky ns

bind all <Return> do_exit
focus .e1 


