/* 
 *  Copyright (C) 2001, 2002, 2009  David Essex, Rildo Pragana.
 *  Copyright (C) 1993, 1991  Rildo Pragana.
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this software; see the file COPYING.  If not, write to
 *  the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 *  Boston, MA 02111-1307 USA
 */

#include "htconfig.h"
#include "htversion.h"
#include "htcoboly.h"
#include "htcoblib.h"
#include "htglobals.h"

/* #define DEBUG_COMPILER_LEVEL    1 */

int main(int argc, char *argv[])
{
  int rc = 1, idx, r;

  prg_name = argv[0];

#ifdef DEBUG_COMPILER_LEVEL
  fprintf (stderr, "htcobol debug 0: main: before initialize_setup\n"); 
#endif

  initialize_setup();

  r = read_compiler_options();
  
  /* process_verbose_options(argc, argv); */

#ifdef DEBUG_COMPILER_LEVEL
  fprintf (stderr, "htcobol debug 1: main: after process_verbose_options\n"); 
#endif
  
  r = process_command_line(argc, argv, &idx);
  if (r != 0)   
     exit(8); 

#ifdef DEBUG_COMPILER_LEVEL
  fprintf (stderr, "htcobol debug 3: main: after process_command_line\n"); 
#endif

  if (idx == argc)   {
      fprintf (stderr, "No input file name provided\n");
      exit (9); 
  }

#ifdef DEBUG_COMPILER_LEVEL
  fprintf (stderr, "htcobol debug 3: main: after file input check\n"); 
#endif
  
  if ((idx + 1) < argc)   {
      fprintf (stderr, "Invalid number of input parameters\n");
      exit (10); 
  }
  
  strcpy (file_path, argv[idx]);
  setup_filenames();

#ifdef DEBUG_COMPILER_LEVEL
  fprintf (stderr, "htcobol debug 4: main: after setup_filenames\n"); 
#endif
  
#ifdef DEBUG_COMPILER_LEVEL
  fprintf (stderr, "htcobol debug 5: main: HTG_compile_level_flag=%d\n", HTG_compile_level_flag); 
#endif

  switch (HTG_compile_level_flag)
  {
    case TCB_COMPILE_LEVEL_PREPROCESS:
      rc = process_pp();
      break;
    
    case TCB_COMPILE_LEVEL_COMPILE:
      rc = process_pp();
      if (rc == 0)
         rc = process_compile();
      break;
    
    case TCB_COMPILE_LEVEL_ASSEMBLE:
    case TCB_COMPILE_LEVEL_EXECUTABLE:
      rc = process_pp();
      if (rc == 0) {
         rc = process_compile();
         if (rc < 8) 
            rc = process_assemble();
      }
      break;
        
    default:
      break;
  }
  
#ifdef DEBUG_COMPILER_LEVEL
  fprintf (stderr, "debug: htcobol 1: HTG_compile_level_flag=%d, HTG_compile_level_type_flag=%d;\n", HTG_compile_level_flag, HTG_compile_level_type_flag);
#endif
  
  if (rc == 0) {
     if (HTG_compile_level_flag == TCB_COMPILE_LEVEL_EXECUTABLE)  {  
        if (HTG_compile_level_type_flag == TCB_COMPILE_TYPE_PROGRAM) 
           rc = process_ld();
        if (HTG_compile_level_type_flag == TCB_COMPILE_TYPE_MODULE) 
           rc = process_shlib_ld();
     }
  }
  else {
     HTG_RETURN_CODE = rc;
  }

  do_file_cleanup();

  if (HTG_verbose_verbose_flag == TRUE ) 
     printf("Compiler return code %d\n", HTG_RETURN_CODE);

  return HTG_RETURN_CODE;
        
}
