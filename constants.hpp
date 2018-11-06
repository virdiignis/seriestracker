//
// Created by prance on 06.11.18.
//

#ifndef SERIESTRACKER_CONSTANTS_HPP
#define SERIESTRACKER_CONSTANTS_HPP

#define MIN_TERM_WIDTH 150

#define MIN_TERM_HEIGHT 5

#define TOP_MENU_ENTRIES {"F2: Series", "F3: Films", "F4: PPVs"}

#define TOP_MENU_ENTRIES_NUM 3

#define BOTTOM_MENU_ENTRIES_SERIES {"q: Quit", "e: edit", "n: new", "r: remove", "f: sfollow/unfollow", "s: Sort"}

#define BOTTOM_MENU_ENTRIES_FILMS {"q: Quit", "e: edit", "n: new", "r: remove", "s: Sort"}

#define BOTTOM_MENU_ENTRIES_PPVS {"q: Quit", "e: edit", "n: new", "r: remove", "f: set reminder", "s: Sort"}

#define BOTTOM_MENU_ENTRIES_SERIES_NUM 6

#define BOTTOM_MENU_ENTRIES_FILMS_NUM 5

#define BOTTOM_MENU_ENTRIES_PPVS_NUM 6

#define BOTTOM_MENU_ENTRIES_SERIES_WIDTHS {maxx - 95, 16, 16, 20, 28, 15}

#define BOTTOM_MENU_ENTRIES_FILMS_WIDTHS {maxx - 95, 25, 25, 30, 15}

#define BOTTOM_MENU_ENTRIES_PPVS_WIDTHS {maxx - 95, 16, 16, 20, 28, 15}

#define SERIES_LIST_PARAMS_WIDTHS {maxx - 50, 28, 12, 10}

#define SERIES_LIST_PARAMS_HEADERS {"Title", "Genre", "Grade", "Followed"}

#define WELCOME_STRING "Welcome to SeriesTracker. Use keys as shown above and below to navigate."

#define FILM_LIST_PARAMS_WIDTHS {maxx - 50, 38, 12}

#define FILM_LIST_PARAMS_HEADERS {"Title", "Genre", "Grade"}

#define PPV_LIST_PARAMS_HEADERS {"Title", "Price", "Date", "Reminder"}

#define KEY_SERIES_LIST 266

#define KEY_FILMS_LIST 267

#define KEY_PPVS_LIST 268

#define KEY_QUIT 'q'

#define KEY_ARROW_DOWN 258

#define KEY_ARROW_UP 259

#define KEY_FOLLOW 'f'

#define KEY_REMOVE 'r'

#define VIEW_WELCOME 0

#define VIEW_SERIES_LIST 1

#define VIEW_FILMS_LIST 2

#define VIEW_PPVS_LIST 3

#define KEY_REMINDER 'f'

#endif //SERIESTRACKER_CONSTANTS_HPP
