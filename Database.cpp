//
// Created by prance on 17.10.18.
//

#include "Database.hpp"


void Database::start() const {
    try {
        if (!fs::exists(BASE_DIR)) fs::create_directory(fs::path(BASE_DIR));
        if (!fs::exists(SERIES_DIR)) fs::create_directory(fs::path(SERIES_DIR));
        if (!fs::exists(FILMS_DIR)) fs::create_directory(fs::path(FILMS_DIR));
        if (!fs::exists(PPVS_DIR)) fs::create_directory(fs::path(PPVS_DIR));
    } catch (fs::filesystem_error &e) {
        throw std::runtime_error("Cannot create db directories!");
    }
}

Database::Database(Pool<Series> &s, Pool<Film> &f, Pool<Ppv> &p) {
    start();
    load(s);
    load(f);
    load(p);
}
template<typename T>
void Database::load(Pool<T> &pool) const {
    int size = 0;
    int *types = nullptr;
    std::string *attrs = nullptr;
    std::string dir;
    if (typeid(T) == typeid(Series)) {
        size = SERIES_DETAILS_NO;
        dir = SERIES_DIR;
        attrs = new std::string[SERIES_DETAILS_NO]SERIES_DETAILS;
        types = new int[SERIES_DETAILS_NO]SERIES_DETAILS_TYPES;
    } else if (typeid(T) == typeid(Film)) {
        size = FILM_DETAILS_NO;
        dir = FILMS_DIR;
        attrs = new std::string[FILM_DETAILS_NO]FILM_DETAILS;
        types = new int[FILM_DETAILS_NO]FILM_DETAILS_TYPES;
    } else if (typeid(T) == typeid(Ppv)) {
        size = PPV_DETAILS_NO;
        dir = PPVS_DIR;
        attrs = new std::string[PPV_DETAILS_NO]PPV_DETAILS;
        types = new int[PPV_DETAILS_NO]PPV_DETAILS_TYPES;
    } else {
        throw std::runtime_error("Incorrect type passed to db_load.");
    }

    std::string temp;
    for (auto &it: fs::directory_iterator(dir)) {
        T n;
        std::ifstream f(it.path());
        if (!f.good()) throw std::runtime_error("Cannot open db file.");
        for (int i = 0; i < size; ++i) {
            f >> temp;
            temp.erase(temp.begin());
            switch (types[i]) {
                case TYPE_BOOL:
                    try {
                        *(std::get<bool *>(n[attrs[i]])) = std::stoi(temp) == 1;
                    } catch (std::invalid_argument &e) {
                        throw std::invalid_argument("Was expecting boolean value from db file, got non-numeric value.");
                    } catch (std::out_of_range &e) {
                        throw std::invalid_argument(
                                "Was expecting boolean value from db file, got non-numeric value bigger than int.");
                    } catch (std::bad_variant_access &e) {
                        throw std::runtime_error("Inconsistent types in config string");
                    }
                    break;
                case TYPE_INT:
                case TYPE_WEEKDAY:
                    try {
                        *(std::get<unsigned short *>(n[attrs[i]])) = static_cast<unsigned short>(std::stoul(temp));
                    } catch (std::invalid_argument &e) {
                        throw std::invalid_argument("Was expecting int value from db file, got non-numeric value.");
                    } catch (std::out_of_range &e) {
                        throw std::invalid_argument(
                                "Was expecting int value from db file, got non-numeric value bigger than long.");
                    } catch (std::bad_variant_access &e) {
                        throw std::runtime_error("Inconsistent types in config string");
                    }
                    break;
                case TYPE_DATE:
                    try {
                        *(std::get<time_t *>(n[attrs[i]])) = static_cast<time_t>(std::stoul(temp));
                    } catch (std::invalid_argument &e) {
                        throw std::invalid_argument("Was expecting int value from db file, got non-numeric value.");
                    } catch (std::out_of_range &e) {
                        throw std::invalid_argument(
                                "Was expecting int value from db file, got non-numeric value bigger than long.");
                    } catch (std::bad_variant_access &e) {
                        throw std::runtime_error("Inconsistent types in config string");
                    }
                    break;
                case TYPE_FLOAT:
                    try {
                        *(std::get<float *>(n[attrs[i]])) = std::stof(temp);
                    } catch (std::invalid_argument &e) {
                        throw std::invalid_argument("Was expecting float value from db file, got non-numeric value.");
                    } catch (std::out_of_range &e) {
                        throw std::invalid_argument(
                                "Was expecting float value from db file, got non-numeric value bigger than float.");
                    } catch (std::bad_variant_access &e) {
                        throw std::runtime_error("Inconsistent types in config string");
                    }
                    break;
                case TYPE_STRING:
                    try {
                        *(std::get<std::string *>(n[attrs[i]])) = temp;
                    } catch (std::bad_variant_access &e) {
                        throw std::runtime_error("Inconsistent types in config string");
                    }
                    break;
                default:
                    throw std::runtime_error("Invalid type number in types array");
            }
        }
        f.close();
        pool += n;
    }

    delete[] types;
    delete[] attrs;
}

void Database::write(Series *&piece) const {
    write(*piece);
}
