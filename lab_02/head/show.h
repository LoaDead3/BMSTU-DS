#ifndef SHOW_H
#define SHOW_H

#define MAX_STR_LEN 30

enum adult_show_type
{
    PLAY, DRAMA, COMEDY
};

struct adult_show
{
    enum adult_show_type genre;
};


enum child_show_type
{
    STORY, PLAY_CH
};

struct child_show
{
    int target_age;
    enum child_show_type genre;
};


struct music_show
{
    char composer[MAX_STR_LEN];
    char country[MAX_STR_LEN];
    int min_age;
    int duration;
};


enum cur_type
{
    CHILD, ADULT, MUSIC
};

struct show
{
    union
    {
        struct adult_show adult;
        struct child_show child;
        struct music_show music;
    };
    int index;
    char theater[MAX_STR_LEN];
    char show[MAX_STR_LEN];
    char director[MAX_STR_LEN];
    int min_price;
    int max_price;
    enum cur_type cur_type;
};

struct show_h_filter
{
    int index;
    int min_age;
    int duration;
};

struct show_h_sort
{
    int index;
    char show[MAX_STR_LEN];
};

#endif
