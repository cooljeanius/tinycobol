ReportGen user notes
--------------------

ReportGen is a replacement for the text-only standard cobol report section. It
is able to generate pretty looking reports in postscript or pdf form with a
minimum of fuss. ReportGen is a tcl program, with a C wrapper for being called
directly from cobol, in a syntax reminiscent of the regular report section. You
have three calls to make it do its job:
	rep_initiate  - before actually reading any report lines;
	rep_generate  - with each line to be processed;
	rep_terminate - to close the output report and flush everything.

There are some problems though to make it work as expected. Tcl have no idea on
how to work with cobol variables, to convert numbers, to add or subtract
values, and so on. Then you will have to convert in cobol all variables to a
displayable form before submitting them to rep_generate. Furthermore, you will
have to add all totalizers that are to be shown on the report, also in a
displayable form. Fortunately, this is easy to do in cobol. What's a MOVE for?

To control the layout of the report pages, you have to write a layout file, but
don't be enfrightened because it is just a simple text file which contains
keywords that represent attributes for each section of the report, as headers,
footers and detail lines.  Those attributes will allow you to chose which font,
color, offset from the beginning of line, vertical spacing before or after a
section, and so on. You can also define in which units will those dimensions be,
such as inches, centimeters, picas, points, and more.

To add columns with barcodes, you will need the GNU Barcode program.
The program "barcode" must also be patch to avoid it automatically inserting a
margin around the barcode image. You have only to edit barcode.h and change the

#define BARCODE_DEFAULT_MARGIN 0

as shon above (the previous value was 10).

Break fields must be declared in the layout file as a Header or Footer, or both
entries, in the order of most priority (break must occur) to less priority
(break occurs only when no other higher-priority break was also found).
When a field break happens, the Footer, and then the Header defined for that
break field is inserted in the report. If the "-eject 1" option is given in the
Header, a page is ejected before sending the Header.

Each column may have -text, -image, -barcode, or -hrule options (but not more 
than one of these at the same time), with replacement values for declared 
cobol variables inside "@@" delimiters, as in 

	-text "Total value @@total-dsp@@"

In this example, the string "@@total-dsp@@" will be replaced by the current
value of the cobol variable "total-dsp".

Barcodes are the same, but the variable's value will be encoded in a suitable
barcode before showing the barcode's image.  The size attributes -width and 
-height will be honored for this image, as well.  Other options (-text, -image)
will not honor the -height attribute.

Image require the name of an encapsulated postscript file with the actual image
to be displayed. Other images formats may be converted by the "convert" utility
found in ImageMagick, a nice and well known image manipulation program.

Horizontal rules may be declared with the -hrule option followed by the height
of the rule. (not in the -height option)

(Please someone else write more here! You may ask me what is not understood :)

Rildo Pragana
