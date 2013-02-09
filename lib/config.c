/* 
 * Copyright (C) 1999-2003 Rildo Pragana, Jim Noeth, 
 *               Andrew Cameron, David Essex.
 * Copyright (C) 1993, 1991  Rildo Pragana.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1,  
 * or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see the file COPYING.LIB.  If
 * not, write to the Free Software Foundation, Inc., 59 Temple Place,
 * Suite 330, Boston, MA 02111-1307 USA

 *
 * TinyCOBOL Run Time Library -- Managing the configuration file functions
 *

*/

#include "config.h"
static int config_loaded = 0;
static int keys_loaded = 0;


static struct config_item *configuration=NULL;

/* install pair key / value */
static void install_keyvalue(char *key,char *value){
    struct config_item *item;    
    struct config_item *last;
    char *p;

    p=key + strlen(value) -1 ;
    while ((*p == ' ')||(*p == '\t')||(*p == '\n')) {
        *p=0;
        p--;
    }
    value+=strspn(value," \t");
    p=value + strlen(value) -1 ;
    while ((*p == ' ')||(*p == '\t')||(*p == '\n')) {
        *p=0;
        p--;
    }

    item=malloc(sizeof(struct config_item));
    memset(item,0,sizeof(struct config_item));
    item->key=strdup(key);
    item->value=strdup(value);
    item->intvalue=atoi(value);
    if (configuration) {
        last=configuration;
        while (last->next) {last=last->next;}
        last->next=item;    
        }
    else        configuration=item;
}
/* load configuration file */

static int load_config() {
    FILE *file;
    char config_line[CONFIG_MAXLINE];
    char *p,*key,*value;        

    if (config_loaded) 
        return 0;

    if ((p = getenv (TCOBRT_CONFIG_DIR)) != NULL) {
        strcpy (config_line, p);
    }
    else {
        strcpy (config_line, TCOB_DEFAULTS_PATH);
    }
    strcat (config_line, LT_DIRSEP_STR);
    strcat (config_line, TCB_RTOPTFILE_DEFAULT);

    if ((file=fopen(config_line, "r")) == NULL){
        return -1;
    }

    fgets (config_line, CONFIG_MAXLINE, file);
    while (!feof (file))  {
        p=strchr(config_line,'#'); 
        if (p)  p[0]='\0'; /* Strip the comments from line */
        key=strtok(config_line,"= \t");
        if (key) {
          value=strtok(NULL,"");
          if (value) {
              install_keyvalue(key,value);
          }
        }
        fgets (config_line, CONFIG_MAXLINE, file); /* get next line */
    }
    fclose(file);
    config_loaded = 1;
    return 1;
}

static struct config_item *find_config_item(char *key){
    struct config_item *item=configuration;        
    while(item){
        if (strcmp(key,item->key)==0) return item;
            item = item->next;
    }
    return NULL;
}

char *tcob_get_str_config(char *key){
    struct config_item *item;
    load_config();
    item = find_config_item(key);
    if (item) 
        return item->value;
    return NULL;
}

int tcob_get_int_config(char *key){
    struct config_item *item;
    load_config();
    item = find_config_item(key);
    if (item) 
        return item->intvalue;
    return 0;
}
/* 
 * Default values
 *
 */

static struct KeyBinding keyBindings[] = {
/*   Key Code   , Action on edit , screen status   */           
  {TCOBKEY_ESCAPE, EDIT_TERMINATE, TCOBKEY_ESCAPE}, /* Escape Key */
  {TCOBKEY_RETURN, EDIT_TERMINATE, 13}, /* For RETURN, we finish the edit mode */
  {KEY_ENTER, EDIT_TERMINATE, 13},     /* ENTER does the same as RETURN */ 

  {KEY_LEFT, EDIT_LEFT, KEY_LEFT},
  {KEY_RIGHT, EDIT_RIGHT, KEY_RIGHT},
  {KEY_HOME, EDIT_FIRST, KEY_HOME},
  {KEY_END, EDIT_LAST, KEY_END},

  {KEY_UP, EDIT_UP_FIELD, KEY_UP},
  {KEY_DOWN, EDIT_DOWN_FIELD, KEY_NEXT},

  {TCOBKEY_TAB, EDIT_NEXT_FIELD, TCOBKEY_TAB},      /* Tab */
  {KEY_BTAB, EDIT_PREV_FIELD, KEY_BTAB},
  {CTRL('n'), EDIT_NEXT_FIELD, 14},
  {CTRL('p'), EDIT_PREV_FIELD, 16},

  {CTRL('f'), EDIT_FIRST_FIELD, 6},
  {CTRL('l'), EDIT_LAST_FIELD, 12},

  {KEY_DC, EDIT_DELETE, KEY_DC},
  {KEY_IC, EDIT_INSERT, KEY_IC},
  {KEY_BACKSPACE, EDIT_BACKSPACE, KEY_BACKSPACE},

  {KEY_PPAGE, EDIT_TERMINATE, KEY_PPAGE},
  {KEY_NPAGE, EDIT_TERMINATE, KEY_NPAGE},
  {KEY_F(1), EDIT_TERMINATE, KEY_F(1)},
  {KEY_F(2), EDIT_TERMINATE, KEY_F(2)},
  {KEY_F(3), EDIT_TERMINATE, KEY_F(3)},
  {KEY_F(4), EDIT_TERMINATE, KEY_F(4)},
  {KEY_F(5), EDIT_TERMINATE, KEY_F(5)},
  {KEY_F(6), EDIT_TERMINATE, KEY_F(6)},
  {KEY_F(7), EDIT_TERMINATE, KEY_F(7)},
  {KEY_F(8), EDIT_TERMINATE, KEY_F(8)},
  {KEY_F(9), EDIT_TERMINATE, KEY_F(9)},
  {KEY_F(10), EDIT_TERMINATE, KEY_F(10)},
  {KEY_F(11), EDIT_TERMINATE, KEY_F(11)},
  {KEY_F(12), EDIT_TERMINATE, KEY_F(12)},
  {0, 0, 0}
};

static int get_key_code(char *key){
    if (strcmp("KEY_ESC",key)==0) return TCOBKEY_ESCAPE;
    if (strcmp("KEY_RETURN",key)==0) return TCOBKEY_RETURN;
    if (strcmp("KEY_ENTER",key)==0) return KEY_ENTER;        
    if (strcmp("KEY_LEFT",key)==0) return KEY_LEFT;
    if (strcmp("KEY_RIGHT",key)==0) return KEY_RIGHT;
    if (strcmp("KEY_HOME",key)==0) return KEY_HOME;
    if (strcmp("KEY_END",key)==0) return KEY_END;
    if (strcmp("KEY_UP",key)==0) return KEY_UP;
    if (strcmp("KEY_DOWN",key)==0) return KEY_DOWN;
    if (strcmp("KEY_TAB",key)==0) return TCOBKEY_TAB;
    if (strcmp("KEY_BTAB",key)==0) return KEY_BTAB;
    if (strcmp("KEY_CTRL_A",key)==0) return CTRL('a');
    if (strcmp("KEY_CTRL_B",key)==0) return CTRL('b');
    if (strcmp("KEY_CTRL_C",key)==0) return CTRL('c');
    if (strcmp("KEY_CTRL_D",key)==0) return CTRL('d');
    if (strcmp("KEY_CTRL_E",key)==0) return CTRL('e');
    if (strcmp("KEY_CTRL_F",key)==0) return CTRL('f');
    if (strcmp("KEY_CTRL_G",key)==0) return CTRL('g');
    if (strcmp("KEY_CTRL_H",key)==0) return CTRL('h');
    if (strcmp("KEY_CTRL_I",key)==0) return CTRL('i');
    if (strcmp("KEY_CTRL_J",key)==0) return CTRL('j');
    if (strcmp("KEY_CTRL_K",key)==0) return CTRL('k');
    if (strcmp("KEY_CTRL_L",key)==0) return CTRL('l');
    if (strcmp("KEY_CTRL_M",key)==0) return CTRL('m');
    if (strcmp("KEY_CTRL_N",key)==0) return CTRL('n');
    if (strcmp("KEY_CTRL_O",key)==0) return CTRL('n');
    if (strcmp("KEY_CTRL_P",key)==0) return CTRL('n');
    if (strcmp("KEY_CTRL_Q",key)==0) return CTRL('n');
    if (strcmp("KEY_CTRL_R",key)==0) return CTRL('n');
    if (strcmp("KEY_CTRL_S",key)==0) return CTRL('n');
    if (strcmp("KEY_CTRL_T",key)==0) return CTRL('n');
    if (strcmp("KEY_CTRL_U",key)==0) return CTRL('n');
    if (strcmp("KEY_CTRL_V",key)==0) return CTRL('n');
    if (strcmp("KEY_CTRL_W",key)==0) return CTRL('n');
    if (strcmp("KEY_CTRL_X",key)==0) return CTRL('n');
    if (strcmp("KEY_CTRL_Y",key)==0) return CTRL('n');
    if (strcmp("KEY_CTRL_Z",key)==0) return CTRL('n');
        
    if (strcmp("KEY_DELETE",key)==0) return KEY_DC;
    if (strcmp("KEY_INSERT",key)==0) return KEY_IC;
    if (strcmp("KEY_BACKSPACE",key)==0) return KEY_BACKSPACE;
    if (strcmp("KEY_NPAGE",key)==0) return KEY_NPAGE;
    if (strcmp("KEY_PPAGE",key)==0) return KEY_PPAGE;
    if (strcmp("KEY_F1",key)==0) return KEY_F(1);
    if (strcmp("KEY_F2",key)==0) return KEY_F(2);
    if (strcmp("KEY_F3",key)==0) return KEY_F(3);
    if (strcmp("KEY_F4",key)==0) return KEY_F(4);
    if (strcmp("KEY_F5",key)==0) return KEY_F(5);
    if (strcmp("KEY_F6",key)==0) return KEY_F(6);
    if (strcmp("KEY_F7",key)==0) return KEY_F(7);
    if (strcmp("KEY_F8",key)==0) return KEY_F(8);
    if (strcmp("KEY_F9",key)==0) return KEY_F(9);
    if (strcmp("KEY_F10",key)==0) return KEY_F(10);
    if (strcmp("KEY_F11",key)==0) return KEY_F(11);
    if (strcmp("KEY_F12",key)==0) return KEY_F(12);
    return -1;        
}

int get_edit_code(char *code){
    if (strcmp("EDIT_FIRST_FIELD",code)==0) return EDIT_FIRST_FIELD;
    if (strcmp("EDIT_LAST_FIELD",code)==0) return EDIT_LAST_FIELD;
    if (strcmp("EDIT_UP_FIELD",code)==0) return EDIT_UP_FIELD;
    if (strcmp("EDIT_DOWN_FIELD",code)==0) return EDIT_DOWN_FIELD;
    if (strcmp("EDIT_NEXT_FIELD",code)==0) return EDIT_NEXT_FIELD;
    if (strcmp("EDIT_PREV_FIELD",code)==0) return EDIT_PREV_FIELD;
    if (strcmp("EDIT_LEFT",code)==0) return EDIT_LEFT;
    if (strcmp("EDIT_RIGHT",code)==0) return EDIT_RIGHT;
    if (strcmp("EDIT_FIRST",code)==0) return EDIT_FIRST;
    if (strcmp("EDIT_LAST",code)==0) return EDIT_LAST;
    if (strcmp("EDIT_INSERT",code)==0) return EDIT_INSERT;
    if (strcmp("EDIT_BACKSPACE",code)==0) return EDIT_BACKSPACE;
    if (strcmp("EDIT_DELETE",code)==0) return EDIT_DELETE;
    if (strcmp("EDIT_TERMINATE",code)==0) return EDIT_TERMINATE;
    if (strcmp("EDIT_CLEAR",code)==0) return EDIT_CLEAR;
    if (strcmp("EDIT_CLEAR_TOEND",code)==0) return EDIT_CLEAR_TOEND;        
    if (strcmp("EDIT_NOP",code)==0) return EDIT_NOP;
    return -1;        
}
static void install_keybinding(char *key,char *value){
    int keycode;
    char *edit_name,*terminate_name;
    int i,edit_code,terminate_value;
    
    keycode=get_key_code(key);
    if (keycode < 0) return ; /* unknown key */
    
    edit_name = strtok(value," \t");
    terminate_name = strtok(NULL," \t");
    
    if (edit_name == NULL) return; /* no action defined */
    edit_code=get_edit_code(edit_name);
    if (terminate_name)  terminate_value=atoi(terminate_name);
    else terminate_value = 0;
    
    i=0;                
    while(keyBindings[i].keyCode){
        if (keyBindings[i].keyCode==keycode){
            keyBindings[i].action=edit_code;
            keyBindings[i].screenStatus=terminate_value;
            return;
        }
        i++;
    }
    return;
}

struct KeyBinding * tcob_get_keybindings(){
    struct config_item *item;
    load_config();
    if (keys_loaded) return keyBindings;
    item=configuration;
    while(item){
        if(strncmp(item->key,"KEY_",4)==0){
            install_keybinding(item->key,item->value);
        }
        item=item->next;
    }
    keys_loaded=1;
    return keyBindings;
}
