//Music Player
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<MMsystem.h>



struct node
	{

	char data[20];
	struct node *prev;
	struct node *next;

	} *head = NULL, *tail = NULL ;


struct node *current_song;
//currently selected song


int display()
	{
    printf("\n----------------");
    printf("\n|  Songs List  |");
    printf("\n----------------\n");

    int i=1;
    //song number

	struct node *temp;
	temp = head;

	if(temp == NULL)
		{
		printf("list is empty ");
		return 0;
		}

	while(1)
		{
		if(temp->next == NULL)
			{
			printf("  %d.%s  \n ",i,temp->data);
			break;
			}

		else
			{
			printf("  %d.%s\n ",i,temp->data);
			temp = temp->next;
			}

        i+=1;
		}
		return 1;
	}





void insertbeg(char item[20])
	{

	struct node *p;
	p = (struct node *)malloc(sizeof(struct node));
	strcpy(p->data,item);

	p->next	=	head;

	if(head!=NULL)
		head->prev = p;
	else
		tail = p;

	head = p;
	p->prev = NULL;

	}




void insertend(char item[20])
	{

	struct node *p;
	p = (struct node *)malloc(sizeof(struct node));
	strcpy(p->data,item);
	p->prev	=	tail;

	if(tail != NULL)
		tail->next = p;
	else
		head = p;

	tail = p;
	p->next = NULL;


	}



int select_song()
    {

        int song_no;
        if(display()==0)
        {
            current_song=NULL;
            return 0;

        }

        printf("\nSelect song no: ");
        scanf("%d",&song_no);

        struct node *temp;

        int i=1;


        temp = head;

        while(temp->next!=NULL)
            {
            if(i==song_no)
                {
                    current_song=temp;
                    return 0;

                }

             i+=1;
             temp=temp->next;

            }
        if(temp->next==NULL && song_no>i)
        {
            printf("\ninvalid choice \n\n");
            current_song=NULL;
        }
        else
            current_song=temp;


    }


int play()
    {
        int loop = 0;
        if(current_song==NULL)
            return 0;
        while(loop==0)
        {
            char selection;
            char link[30]="songs/";
            strcat(link,current_song->data);

            PlaySound(TEXT(link), NULL, SND_FILENAME | SND_ASYNC );
            printf("\n\nplaying %s.........\n",current_song->data);
            while(loop==0)
            {


                printf("NEXT->(N) | PREV->(P) | STOP->(S)\n");
                fscanf(stdin, " %c", &selection);
                if(selection=='n')
                {
                    if(current_song->next==NULL)
                        current_song=head;
                    else
                        current_song=current_song->next;

                    break;
                }

                else if(selection=='p')
                     {
                    if(current_song->prev==NULL)
                        current_song=tail;
                    else
                        current_song=current_song->prev;

                    break;
                    }
                else if(selection=='s')
                {


                    PlaySound(TEXT(NULL), NULL, SND_FILENAME | SND_ASYNC );
                    loop=1;
                }

                else
                    printf("\ninvalid choice\n\n\n");
            }

        }

    }



int deletepos()
	{

        struct node *temp, *loc;
        select_song();
        if(current_song==NULL)
            return 0;
        if(head == current_song && tail == current_song)
        {
            head = NULL;
            tail = NULL;
            free(current_song);
        }
        else if(current_song->prev==NULL)
        {
            head = current_song->next;
            head->prev=NULL;
            free(current_song);
        }
        else if(current_song->next == NULL)
        {
            tail = current_song->prev;
            tail->next = NULL;
            free(current_song);
        }
        else
        {

            loc = current_song->prev;
            temp = current_song->next;
            loc->next = temp;
            temp->prev = loc;
            free(current_song);
        }



	}




void main()
	{

	int c;
	char d[20];

	while(c!=8)
		{
	printf("\n\n"
        "------------------------\n"
		"|        Options       |\n"
		"------------------------\n"
		"|   1.Add Song @ Top   |\n"
		"|   2.Add song @ End   |\n"
		"|   3.Delete Song      |\n"
		"|   4.display          |\n"
		"|   5.play song        |\n"
		"|   6.exit             |\n"
		"------------------------\n");

		printf("  Enter the choice : ");
		scanf("%d",&c);
		printf("\n\n");

		if(c == 1)
			{
			printf("  Song Title : ");
			scanf("%s",&d);
			insertbeg(d);
			}

		else if(c == 2)
			{
            printf("  Song Title : ");
			scanf("%s",&d);
			insertend(d);
			}

        else if(c == 3)
			{
			deletepos();
			}



			else if(c == 4)
				display();

            else if(c == 5)
				{

                do{
                        if(select_song()==0)
                            break;

                }while(current_song == NULL);


                play();
				}


            else if(c== 6)
                break;
            else
                printf("   invalid choice   \n");



		}
	}
