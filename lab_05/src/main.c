#include <stdio.h>
#include <string.h>
#include "point_list.h"


int main(int argc, char *argv[]) {
    intrusive_list intrusiveList;


    init_list(&intrusiveList);

    char *how_to_read = argv[1]; // loadtext or loadbin
    char *filename = argv[2];
    char *action = argv[3];
    char *action_argument = argc > 4 ? argv[4] : NULL;


    if (strcmp(how_to_read, "loadtext") == 0) {
        read_list_from_txt(&intrusiveList, filename);
    } else {
        read_list_from_bin(&intrusiveList, filename);
    }

    if (strcmp(action, "savetext") == 0) {
        save_list_to_txt(&intrusiveList, action_argument);
    } else if (strcmp(action, "savebin") == 0) {
        save_list_to_bin(&intrusiveList, action_argument);
    } else if (strcmp(action, "print") == 0) {
        print_points_by_format(&intrusiveList, action_argument);
    } else { // count
        int result = count(&intrusiveList);
        printf("%d\n", result);
    }

    remove_all_points(&intrusiveList);

    return 0;
}