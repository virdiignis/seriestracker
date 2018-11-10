//
// Created by prance on 06.11.18.
//

#ifndef SERIESTRACKER_CONSTANTS_HPP
#define SERIESTRACKER_CONSTANTS_HPP

#define WELCOME_STRING "Welcome to SeriesTracker. Use keys as shown above and below to navigate."

//Interface views
#define VIEW_WELCOME 0
#define VIEW_SERIES_LIST 1
#define VIEW_FILMS_LIST 2
#define VIEW_PPVS_LIST 3
#define VIEW_SERIES_FILTERED 4
#define VIEW_SERIES 5
#define VIEW_FILM 6
#define VIEW_PPV 7
#define VIEW_SERIES_F 8
#define VIEW_EDIT 9

//Minimal terminal size
#define MIN_TERM_WIDTH 80
#define MIN_TERM_HEIGHT 5

//Top render
#define TOP_MENU_ENTRIES_NUM 3
#define TOP_MENU_ENTRIES {"F2: Series", "F3: Films", "F4: PPVs"}

//Bottom render
#define BOTTOM_MENU_ENTRIES_SERIES_NUM 7
#define BOTTOM_MENU_ENTRIES_SERIES {"q: Quit", "d: details", "n: new", "^r: remove", "f: follow/unfollow", "^f: filter followed", "s: Sort"}
#define BOTTOM_MENU_ENTRIES_SERIES_WIDTHS {max_x - 82, 12, 8, 12, 20, 21, 9}

#define BOTTOM_MENU_ENTRIES_FILMS_NUM 5
#define BOTTOM_MENU_ENTRIES_FILMS {"q: Quit", "d: details", "n: new", "^r: remove", "s: Sort"}
#define BOTTOM_MENU_ENTRIES_FILMS_WIDTHS {max_x - 41, 12, 8, 12, 9}

#define BOTTOM_MENU_ENTRIES_PPVS_NUM 6
#define BOTTOM_MENU_ENTRIES_PPVS {"q: Quit", "d: details", "n: new", "^r: remove", "f: set reminder", "s: Sort"}
#define BOTTOM_MENU_ENTRIES_PPVS_WIDTHS {max_x - 95, 16, 16, 20, 28, 15}

//Lists headers
#define SERIES_LIST_PARAMS 4
#define SERIES_LIST_PARAMS_HEADERS {"Title", "Genre", "Grade", "Followed"}
#define SERIES_LIST_PARAMS_WIDTHS {max_x - 50, 28, 12, 10}

#define FILM_LIST_PARAMS 3
#define FILM_LIST_PARAMS_HEADERS {"Title", "Genre", "Grade"}
#define FILM_LIST_PARAMS_WIDTHS {max_x - 50, 38, 12}

#define PPV_LIST_PARAMS 4
#define PPV_LIST_PARAMS_HEADERS {"Title", "Price", "Start time", "Reminder"}
#define PPV_LIST_PARAMS_WIDTHS {max_x - 68, 28, 30, 10}

//Keys
#define KEY_SERIES_LIST 266
#define KEY_FILMS_LIST 267
#define KEY_PPVS_LIST 268
#define KEY_QUIT 'q'
#define KEY_ARROW_DOWN 258
#define KEY_ARROW_UP 259
#define KEY_FOLLOW 'f'
#define KEY_FILTER 6
#define KEY_REMINDER 'f'
#define KEY_REMOVE 18
#define KEY_SORT 's'
#define KEY_DETAILS 'd'
#define KEY_EDIT 'e'

#define WEEKDAYS {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}


#endif //SERIESTRACKER_CONSTANTS_HPP
