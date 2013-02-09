void
subrot( char *arg ) {
	char s[21];
	/* we must put a terminating null at the C string */
	s[20] = 0;
	/* move the cobol argument to here (it's _not_ null terminated) */
	memmove(s,arg,20);
	/* show it to see if everything was well done */
	printf("Received argument: [%s]\n",s);
}

