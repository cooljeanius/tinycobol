*
* copy file to ease the use of the new features of screen section.
*
* You can now define field on the screen section like:
*
* 01 field-scr pic x(4) line 1 col 1 foreground-color bright-white 
*                                    background-color red.
*
*
* You can also use 'color' like this
*
* 01 field-scr pic x(4) line 1 col 1 color color-wor. 
*
* and then befor displaying
* compute color-wor = bright-white + background-red + blink. 
*
* you can also use variabnle lines and columns like that
*
* 01 field-scr pic x(4) line line-wor col col-wor color color-wor.
*
* NOTE: line-wor,col-wor and color-wor must be s9(.) comp fields.
*
       77 black			pic s9(5) comp value 0.
       77 blue			pic s9(5) comp value 1.
       77 green			pic s9(5) comp value 2.
       77 cyan			pic s9(5) comp value 3.
       77 red			pic s9(5) comp value 4.
       77 magenta		pic s9(5) comp value 5.
       77 brown			pic s9(5) comp value 6.
       77 white			pic s9(5) comp value 7.

       77 grey				pic s9(5) comp value 8.
       77 bright-blue		pic s9(5) comp value 9.
       77 bright-green		pic s9(5) comp value 10.
       77 bright-cyan		pic s9(5) comp value 11.
       77 bright-red		pic s9(5) comp value 12.
       77 bright-magenta	pic s9(5) comp value 13.
       77 yellow			pic s9(5) comp value 14.
       77 bright-white		pic s9(5) comp value 15.

       77 background-black	pic s9(5) comp value 0.
       77 background-blue	pic s9(5) comp value 16.
       77 background-green	pic s9(5) comp value 32.
       77 background-cyan	pic s9(5) comp value 48.
       77 background-reg	pic s9(5) comp value 64.
       77 background-magenta	pic s9(5) comp value 80.
       77 background-brown	pic s9(5) comp value 96.
       77 background-white	pic s9(5) comp value 112.

       77 color-highlight      	pic s9(5) comp value 512.
       77 color-lowlight      	pic s9(5) comp value 1024.
       77 color-underline      	pic s9(5) comp value 2048.
       77 color-reverse		pic s9(5) comp value 4096.
       77 color-blink		pic s9(5) comp value 8192.
*
* This field it to help people handle key codes.
* You have to define in the configuration section
*     crt status is crt-status.
* and the on the program you can use sentences like this:
*
*   accept some-var.
*   if f3
*      stop run
*   end-if.
*
* or like this:
*
*   accept some-var.
*   evaluate true
*      when ret perform function1 
*      when f1  perform function1 
*      when f2  perform function1 
*      when f3  stop run 
*   end-evaluate.
*
*

       01 crt-status            pic x(4).
          88 ret                value "0013".
          88 f1                 value "0265".
          88 f2                 value "0266".
          88 f3                 value "0267".
          88 f4                 value "0268".
          88 f5                 value "0269".
          88 f6                 value "0270".
          88 f7                 value "0271".
          88 f8                 value "0272".
          88 f9                 value "0273".
          88 f10                value "0274".
          88 f11                value "0275".
          88 f12                value "0276".
          88 up-key             value "0259".
          88 down-key           value "0367".
          88 pgup               value "0339".
          88 pgdown             value "0338".
       
