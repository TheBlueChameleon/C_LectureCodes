#define _GNU_SOURCE       // use all features from unistd.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>       // some file system functions...
#include <dirent.h>       // ... and some more ...
#include <sys/stat.h>     // ... and even more.

// ========================================================================= //
// handle a list of strings

typedef struct {
  unsigned int N;       // number of strings in the list
  char **      items;   // the list itself
} * stringlist;

// ------------------------------------------------------------------------- //

stringlist make_stringlist() {
  /* Create a well-defined initial state so that the other methods don't have
   * to do excessive error-checking
   */
  
  stringlist reVal = malloc(sizeof(*reVal));
  
  if (reVal) {
    reVal->N     = 0;
    reVal->items = NULL;
  } else {
    printf("Error in make_stringlist: Could not allocate memory.\n");
    return NULL;
  }
  
  return reVal;
}

void free_stringlist(const stringlist list) {
  /* frees all memory occupied by the components of a stringlist.
   */
  
  // first, free the items themselves
  for (unsigned int i=0; i<list->N; i++) {
    if (list->items[i]) {free(list->items[i]);}
  }
  
  // then free the list of items
  free(list->items);
  
  // and finally, free the struct
  free(list);
}

// ......................................................................... //

int append_to_stringlist(const stringlist list, const char * item) {
  /* adds an item to the end of a stringlist.
   * returns number of items in the list on success or -1 on failure.
   */
  
  // check whether a NULL pointer was passed
  if (!list) {
    printf("Error in append_to_stringlist: Invalid list.\n");
    return -1;
  }
  
  // make a copy of the item to be added to the list
  char * newItem = malloc(strlen(item) + 1);
  if (!newItem) {
    printf("Error in append_to_stringlist: Not enough memory for new item.\n");
    return -1;
  }
  strcpy(newItem, item);
  
  // make the list one item longer
  char ** longerList = realloc(list->items, (list->N+1) * sizeof(*longerList));
  if (!longerList) {
    printf("Error in append_to_stringlist: Could not expand list.\n");
    free(newItem);
    return -1;
  }
  
  list->items = longerList;
  list->items[list->N] = newItem;
  
  return ++list->N;
}

// ......................................................................... //

char * get_stringlist_item(const stringlist list, const unsigned int i) {
  /* access to stringlist items with error checks
   */
  
  // check whether a NULL pointer was passed
  if (!list) {
    printf("Error in get_stringlist_item: Invalid list.\n");
    return NULL;
  }
  
  // check if index out of boundaries
  if (i < list->N) {
    return list->items[i];
    
  } else {
    printf("Error in get_stringlist_item: Invalid index.\n");
    return NULL;
  }
}

// ......................................................................... //

unsigned int get_stringlist_length(const stringlist list) {
  if (!list) {
    printf("Error in get_stringlist_length: Invalid list.\n");
    return 0;
  }
  
  return list->N;
}

// ========================================================================= //
// create lists of files and directories in the current working directory

typedef enum {listtype_files, listtype_directories} listtypes;

stringlist get_directory_entries (const listtypes type) {
  stringlist reVal = make_stringlist();
  
  DIR * filesystem_handle = opendir(".");
      // "." represents current work directory
      // opendir returns NULL if it couldn't open the directory 
  
  struct dirent * directory_entry;
      // will hold name of one item in the directory
  struct stat     statbuffer;
      // will hold kind of one item in the directory (file or folder)
  
  if (filesystem_handle == NULL) {
    printf("Error in get_subdirectories: Could not open current directory\n");
    free_stringlist(reVal);
    return NULL;
  }
  
    // read new entries from the directory as long as there are any.
  while (  (directory_entry = readdir(filesystem_handle)) != NULL  ) {
    // skip special file system elements
    if ((strcmp(directory_entry->d_name, "." ) == 0) ||
        (strcmp(directory_entry->d_name, "..") == 0)
    ) {continue;}
    
    // analyze type of directory enty
    if(  stat(directory_entry->d_name, &statbuffer) == -1  ) {
      printf("Error in get_subdirectories: "
             "Could not determine kind of entry %s\n", 
             directory_entry->d_name);
      free_stringlist(reVal);
      return NULL;
    }
    
    int entry_is_directory = S_ISDIR(statbuffer.st_mode);
    int condition_to_add =
       ( entry_is_directory && (type == listtype_directories)) ||
       (!entry_is_directory && (type == listtype_files      ));
    
    if (condition_to_add) {
      append_to_stringlist(reVal, directory_entry->d_name);
    }
    
  }
  
  closedir(filesystem_handle);
  return reVal;
}

// ========================================================================= //
// recursive traversal of file system

void print_indented(const char * text, const unsigned int n) {
  for (unsigned int i=0; i<n; i++) {printf("  ");}
  
  printf("%s\n", text);
}

// ------------------------------------------------------------------------- //

void showtree(char * startDir) {
  static unsigned int indent_level = 0;
  int                 flag_free_startDir = 0;
  
  if (!startDir) {
    // use current work directory if nothing else was specified.
    startDir = get_current_dir_name();
        // this function uses malloc, thus a free() is needed later
    flag_free_startDir = 1;
        // store information: free is needed.
  }
  
  if (  chdir(startDir)  ) {
    // switch to directory startDir. Return 0 on success, -1 otherwise
    
    printf("\x1b[91m");   // switch to colour red for error output
    print_indented("(invalid directory)", indent_level);
    printf("\033[m");     // restore normal colours
    if (flag_free_startDir) {free(startDir);}
    return;
  }
  
  printf("\x1b[96m");   // show directories in bright cyan
  print_indented(startDir, indent_level);
  printf("\033[m");     // restore normal colours
  
  // get list of directories and go into recursion
  stringlist subdirs = get_directory_entries(listtype_directories);
  if (subdirs) {
    for (unsigned int i=0; i<get_stringlist_length(subdirs); i++) {
      indent_level++;
      showtree(get_stringlist_item(subdirs, i));
      chdir("..");
      indent_level--;
    }
    free_stringlist(subdirs);
  }
  
  // get list of files
  stringlist files = get_directory_entries(listtype_files);
  if (files) {
    for (unsigned int i=0; i<get_stringlist_length(files); i++) {
      print_indented(get_stringlist_item(files, i), indent_level + 1);
    }
    free_stringlist(files);
  }
  
  if (flag_free_startDir) {free(startDir);}
}

// ========================================================================= //

int main (int argc, char ** argv) {
  if (argc) {showtree(argv[1]);}
  else      {showtree(NULL   );}
}
