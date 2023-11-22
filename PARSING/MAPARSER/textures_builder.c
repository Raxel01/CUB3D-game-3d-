#include "../../HEADER/Parsing.h"

t_textures *build_member(char *t_path, enum e_path direct)
{
    t_textures *node;

    node = malloc(sizeof(t_textures));
    if(!node)
        return (allocation_error(), NULL);
    node->path = t_path;
    node->type = direct;
    node->size = 0;
    node->next = NULL;
    return (node);
}

void    addmember(t_textures **head, t_textures *newmember)
{
    t_textures *cursur;

    if (*head == NULL)
    {
        (*head) = newmember;
        (*head)->size++;
    }
    else
    {
        cursur = *head;
        while (cursur->next)
            cursur = cursur->next;
        cursur->next = newmember;
        (*head)->size++;
    }
}

t_rgb   *creatnode(long *purergb, enum e_floorciel it_type)
{
    t_rgb   *node;

    node = malloc(sizeof(t_rgb));
    if (!node)
        return(allocation_error(), NULL);
    node->rgb = purergb;
    node->type = it_type;
    node->member = 0;
    node->next = NULL;
    return (node);
}

void    linknodes(t_rgb **head, t_rgb *newelem)
{
    t_rgb *cursur;

    if (*head == NULL)
    {
        (*head) = newelem;
        (*head)->member++;
    }
    else
    {
        cursur = *head;
        while (cursur->next)
            cursur = cursur->next;
        cursur->next = newelem;
        (*head)->member++;
    }
}