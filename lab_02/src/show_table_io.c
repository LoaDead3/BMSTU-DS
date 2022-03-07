#include "../head/show_table_io.h"

int input_interface_perm;

int input_str(FILE *f, char *s)
{
    *s = '\n';
    char *rc;
    while (*s == '\n')
    {
        rc = fgets(s, MAX_STR_LEN + 3, f);
        if (rc == NULL)
            break;
    }
    if (rc == NULL || *rc == '\n')
        return FILE_END;
    char *n_ptr = strrchr(s, '\n');
    if (n_ptr != NULL)
        *n_ptr = '\0';
    if (strlen(s) > MAX_STR_LEN)
        return TO_LONG_STR;
    return 0;
}

int input_digit(FILE *f, int *d)
{
    char tmp_year_char[MAX_STR_LEN + 3];
    char *rc = fgets(tmp_year_char, MAX_STR_LEN + 3, f);
    *d = atoi(tmp_year_char);
    if (rc == NULL || *rc == '\n' || *d <= 0 || strchr(tmp_year_char, '.') != NULL)
        return WRONG_DATA;
    return 0;
}

void str_asign(char *dst, char *src)
{
    while (*dst++ = *src++);
}

int exp_mem(struct show **arr, int num_of_elem)
{
    *arr = realloc(*arr, sizeof(struct show) * num_of_elem);
    if (!(*arr))
        return MEM_ERROR;
    return 0;
}

int adult_show_input(FILE *f, struct show *n)
{
    int rc = 0, tmp = 0;
    if (input_interface_perm)
        printf("Choice item type\n1-play\n2-drama\n3-comedy\nChoice:");
    rc = input_digit(f, &tmp);
    if (rc)
        return rc;
    switch (tmp)
    {
        case 1:
        {
            n->adult.genre = PLAY;
            break;
        }
        case 2:
        {
            n->adult.genre = DRAMA;
            break;
        }
        case 3:
        {
            n->adult.genre = COMEDY;
            break;
        }
        default:
            return WRONG_DATA;
    }
    return 0;
}

int child_show_input(FILE *f, struct show *n)
{
    int rc = 0, d;
    if (input_interface_perm)
        printf("Input target age:");
    rc = input_digit(f, &d);
    if(d > 18)
        return WRONG_DATA;
    if (rc)
        return rc;
    n->child.target_age = d;
    if (input_interface_perm)
        printf("Choice item type\n1-story\n2-play\nChoice:");
    rc = input_digit(f, &d);
    if (rc)
        return rc;
    switch (d)
    {
        case 1:
        {
            n->child.genre = PLAY_CH;
            break;
        }
        case 2:
        {
            n->child.genre = STORY;
            break;
        }
        default:
            return WRONG_DATA;
    }
    return 0;
}

int music_show_input(FILE *f, struct show *n)
{
    char buff[MAX_STR_LEN + 3];
    int rc, tmp_d;
    if (input_interface_perm)
        printf("Input composer:");
    rc = input_str(f, buff);
    if (rc)
        return rc;
    str_asign(n->music.composer, buff);
    if (input_interface_perm)
        printf("Input country:");
    rc = input_str(f, buff);
    if (rc)
        return rc;
    str_asign(n->music.country, buff);
    if (input_interface_perm)
        printf("Input min age:");
    rc = input_digit(f, &tmp_d);
    if (rc)
        return rc;
    n->music.min_age = tmp_d;
    if (input_interface_perm)
        printf("Input duration:");
    rc = input_digit(f, &tmp_d);
    if (rc)
        return rc;
    n->music.duration = tmp_d;
    return 0;
}

int input_elem(FILE *f, struct show *n)
{
    char buff[MAX_STR_LEN + 3];
    int choise_t, rc;
    if (input_interface_perm)
        printf("Input theater:");
    rc = input_str(f, buff);
    if (rc)
    {
        return rc;
    }
    str_asign(n->theater, buff);
    if (input_interface_perm)
        printf("Input show name:");
    rc = input_str(f, buff);
    if (rc)
    {
        return rc;
    }
    str_asign(n->show, buff);
    if (input_interface_perm)
        printf("Input director:");
    rc = input_str(f, buff);
    if (rc)
    {
        return rc;
    }
    str_asign(n->director, buff);
    if (input_interface_perm)
        printf("Input min price:");
    rc = input_digit(f, &n->min_price);
    if (rc)
    {
        return rc;
    }
    if (input_interface_perm)
        printf("Input max price:");
    rc = input_digit(f, &n->max_price);
    if (rc)
    {
        return rc;
    }
    if (input_interface_perm)
        printf("Choice item type\n1-Child\n2-Aduit\n3-Music\nChoice:");
    rc = input_digit(f, &choise_t);
    if (rc)
    {
        return rc;
    }
    switch (choise_t)
    {
        case 1:
        {
            n->cur_type = CHILD;
            rc = child_show_input(f, n);
            break;
        }
        case 2:
        {
            n->cur_type = ADULT;
            rc = adult_show_input(f, n);
            break;
        }
        case 3:
        {
            n->cur_type = MUSIC;
            rc = music_show_input(f, n);
            break;
        }
        default:
            return WRONG_DATA;
    }
    if (rc)
    {
        return rc;
    }
    return 0;
}

int input(FILE *f, struct show_table *table)
{
    input_interface_perm = (f == stdin) ? 1 : 0;
    int mem_size = DEFAULT_SIZE;
    table->size = 0;
    table->list = calloc(mem_size, sizeof(struct show));
    if (!table->list)
    {
        free(table->list);
        return MEM_ERROR;
    }
    int rc = 0;
    while (rc == 0)
    {
        struct show tmp;
        tmp.index = table->size;
        if (tmp.index == 4)
            printf("");
        rc = input_elem(f, &tmp);
        if (rc)
        {
            if (rc == FILE_END)
                break;
            else
            {
                free(table->list);
                return rc;
            }
        }
        if (table->size == mem_size)
        {
            mem_size *= EXP_COEFF;
            rc = exp_mem(&table->list, mem_size);
            if (rc)
            {
                free(table->list);
                return rc;
            }
        }
        table->list[table->size++] = tmp;
    }
    if (table->size == 0)
    {
        free(table->list);
        return NO_DATA;
    }
    rc = exp_mem(&table->list, table->size);
    if (rc)
    {
        free(table->list);
        return rc;
    }
    return 0;
}

void child_print(struct show *n)
{
    printf("%7s|", "Child");
    switch (n->child.genre)
    {
        case STORY:
            printf("%7s|", "story");
            break;
        case PLAY_CH:
            printf("%7s|", "play");
            break;
        default:
            break;
    }
    printf("%11d|%31s|%31s|%8s|%9s|", n->child.target_age, "-/-", "-/-", "-/-", "-/-");
}

void adult_print(struct show *n)
{
    printf("%7s|", "Adult");
    switch (n->adult.genre)
    {
        case DRAMA:
            printf("%7s|", "drama");
            break;
        case PLAY:
            printf("%7s|", "play");
            break;
        case COMEDY:
            printf("%7s|", "comedy");
            break;
        default:
            break;
    }
    printf("%11s|%31s|%31s|%8s|%9s|", "-/-", "-/-", "-/-", "-/-", "-/-");
}

void music_print(struct show *n)
{
    printf("%7s|%7s|%11s|%31s|%31s|%8d|%9d|", "Music", "-/-", "-/-",
           n->music.composer, n->music.country, n->music.min_age, n->music.duration);
}

void print_elem(struct show *elem)
{
    printf("%5d|%31s|%31s|%31s|%7d-%7d|",
           elem->index, elem->theater, elem->show, elem->director,
           elem->min_price, elem->max_price);
    switch (elem->cur_type)
    {
        case CHILD:
            child_print(elem);
            break;
        case ADULT:
            adult_print(elem);
            break;
        case MUSIC:
            music_print(elem);
            break;
        default:
            break;
    }
    printf("\n");
}

void print_title()
{
    printf("\n\n");
    printf("%5s|%31s|%31s|%31s|%15s|"
           "%7s|%7s|%11s|%31s|%31s|%8s|%9s|\n",
           "Index", "Theater", "Show name", "Director", "Price",
           "Type", "Genre", "Target age", "Composer", "Country", "Min age", "Duration");
}

void print(struct show_table *table)
{
    print_title();
    for (int i = 0; i < table->size; i++)
        print_elem(&table->list[i]);
    printf("\n");
}

void print_table_with_key_sort(struct show_table *table, struct show_table_h_sort *handl)
{
    print_title();
    for (int i = 0; i < table->size; i++)
        print_elem(&table->list[handl->list[i].index]);
    printf("\n");
}

void print_table_with_key_filter(struct show_table *table, struct show_table_h_filter *handl)
{
    print_title();
    for (int i = 0; i < handl->size; i++)
        print_elem(&table->list[handl->list[i].index]);
    printf("\n");
}

int add(struct show_table *table)
{
    input_interface_perm = 1;
    table->list = realloc(table->list, sizeof(struct show) * (table->size + 1));
    if (!table->list)
        return MEM_ERROR;
    struct show tmp;
    int rc = input_elem(stdin, &tmp);
    if (rc)
        return rc;
    tmp.index = table->size;
    table->list[table->size] = tmp;
    table->size++;
    return 0;
}
