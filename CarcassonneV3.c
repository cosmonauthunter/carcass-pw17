#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Tiles
{
	char segments[5];
	char special[10];
	int quantity;
	int id;
};
struct Tilesplaced
{
	char segments[5];
	char special[10];
	int id;
};
struct Tiles tile[30];
struct Tilesplaced tileplaced[100];

void tileinfoall( struct Tiles *tile ) 
{
   printf( "Tile Segments : %s		", tile->segments);
   printf( "Special : %s	", tile->special);
   printf( "Quantity : %d		", tile->quantity);
   printf( "ID : %d\n",tile->id); 
}

void tileinfoavilable( struct Tiles *tile ) 
{
	if(tile->quantity>0)
	{
   		printf( "Tile Segments : %s		", tile->segments);
		printf( "Special : %s		", tile->special);
		printf( "Quantity : %d		", tile->quantity);
		printf( "ID : %d\n",tile->id); 
	}
}

void yourtiles(int tot)
{
	int t=1;
	for(t;t<=tot;t++)
	tileinfoavilable(&tile[t]);
}

int quantitycheck(int typesoftiles)
{
	int number=0;
	int t;
	for(t=0;t<typesoftiles;t++)
	{
		number=number+tile[t].quantity;
	}
	return number;
}

void tileset(int a,int b,int set[a][b], int typesoftiles)
{
	int t,y,q=0,l=0,c=0,e=0,d,lx,ly;
	for(y=0;y<a;y++)
	{
		for(t=0;t<b;t++)
		{
			if(set[t][y]==0)
			{
				q++;
			}
			else
			{
				t=b;
				l++;
				if(l==1)
				{
					d=e;
					e=b+1;
				}
			}
			if(q==b)
			{
				if(l<1)
				e++;
				else
				e--;
			}
		}
		q=0;
	}
	ly=e;
	e=0;
	l=0;
	printf("\n");
	for(y=0;y<b;y++)
	{
		for(t=0;t<a;t++)
		{
			if(set[y][t]==0)
			{
				q++;
			}
			else
			{
				t=a;
				l++;
				if(l==1)
				{
					c=e;
					e=a+1;
				}
			}
			if(q==(a-1))
			{
				if(l<1)
				e++;
				else
				e--;
			}
		}
		q=0;
	}
	lx=e;
	printf("\n    ");
	for(t=c; t<lx-1; t++)
	{
		if(t<10)
		printf("   %d  ",t);
		if(t<100&&t>9)
		printf("  %d  ",t);
		if(t<1000&&t>99)
		printf("  %d ",t);
	}
	printf("\n");
	for(t=d; t<ly-1; t++)
	{
		printf("\n    ");
		for(y=c; y<lx-1; y++)
		printf("   %c  ",tileplaced[set[y][t]].segments[0]);
		printf("\n");
		if(t<10)
		printf("%d   ",t);
		if(t<100&&t>9)
		printf("%d  ",t);
		if(t<1000&&t>99)
		printf("%d ",t);
		for(y=c; y<lx; y++)
		{
			printf(" %c ",tileplaced[set[y][t]].segments[3]);
			if(strcmp(tileplaced[set[y][t]].special, "Temple")==0)
			printf("%c %c",'T',tileplaced[set[y][t]].segments[1]);
			else
			{
				if(strcmp(tileplaced[set[y][t]].special, "Emblem")==0)
				printf("%c %c",'E',tileplaced[set[y][t]].segments[1]);
				else
				printf("  %c",tileplaced[set[y][t]].segments[1]);
			}
		}
		printf("\n    ");
		for(y=c; y<lx; y++)
		printf("   %c  ",tileplaced[set[y][t]].segments[2]);
	}
	printf("\n");
}

int choicevalid(int chosen,int typesoftiles)
{
	int validity=0;
	while(validity==0)
	{
		if(chosen>typesoftiles||chosen<0)
		{
			printf("Wrong id, try again\n");
			scanf("%d", &chosen);
		}
		else
		{
			if(tile[chosen].quantity==0)
			{
				printf("Tile unavilable, choose other");
				scanf(" %d", &chosen);
			}
			else
			validity=1;		
		}
	}
	return 1;
}

int ifempty(int a, int b, int coordx,  int coordy, int set[a][b])
{
	if(set[coordx][coordy]!=0)
	return 0;
	return 1;
}

int placementvalid(int a, int b, int coordx,  int coordy, int set[a][b])
{
	int valid=0,zero=0;

	if(tileplaced[set[coordx][coordy]].segments[3]==tileplaced[set[coordx-1][coordy]].segments[1])
	valid++;
	if(set[coordx-1][coordy]==0)
	zero++;
	if(tileplaced[set[coordx][coordy]].segments[1]==tileplaced[set[coordx+1][coordy]].segments[3])
	valid++;
	if(set[coordx+1][coordy]==0)
	zero++;
	if(tileplaced[set[coordx][coordy]].segments[2]==tileplaced[set[coordx][coordy-1]].segments[0])
	valid++;
	if(set[coordx][coordy-1]==0)
	zero++;
	if(tileplaced[set[coordx][coordy]].segments[0]==tileplaced[set[coordx][coordy+1]].segments[2])
	valid++;
	if(set[coordx][coordy+1]==0)
	zero++;
//	printf("valid %d zero %d\n",valid,zero);
	if(valid+zero==4&&valid>0)
	return 1;
}

void rotationpre(int rotations, int tileid)
{
	char c[10];
	rotations=rotations % 4;
	c[(0+rotations) % 4]=tile[tileid].segments[0];
	c[(1+rotations) % 4]=tile[tileid].segments[1];
	c[(2+rotations) % 4]=tile[tileid].segments[2];
	c[(3+rotations) % 4]=tile[tileid].segments[3];
	printf("\n   %c",c[0]);
	printf("\n %c ",c[3]);
	if(strcmp(tile[tileid].special, "Temple")==0)
	printf("%c %c",'T',c[1]);
	else
	{
		if(strcmp(tile[tileid].special, "Emblem")==0)
		printf("%c %c",'E',c[1]);
		else
		printf("  %c",c[1]);
	}
	printf("\n   %c\n\n",c[2]);

}

void rotation(int rotations, int tileid)
{
	int t,o;
	char v1,v2;
	for(t=0;t<rotations;t++)
	{
		v1=tile[tileid].segments[1];
		tile[tileid].segments[1]=tile[tileid].segments[0];
		v2=tile[tileid].segments[2];
		tile[tileid].segments[2]=v1;
		v1=tile[tileid].segments[3];
		tile[tileid].segments[3]=v2;
		tile[tileid].segments[0]=v1;
	}
}

int rotationchoice(int ch)
{
	int punch=0, rota;
	char word;
	while(punch==0)
	{
		printf("Choose number of rotations of the tile\n");
		scanf("%d", &rota);
		printf("tile %s\n",tile[ch].segments);
		rotationpre(rota,ch);
		printf("Place the tile? (y/n)\n");
		scanf(" %c",&word);				
		if(word==121)
		{
			rotation(rota,ch);
			punch=1;
		}
		if(word!=110&&word!=121)
		{
			punch=0;
			while(punch==0)
			{
				printf("Wrong command, try again\n");
				scanf(" %c", &word);
				if(word==121)
				{
					rotation(rota,ch);
					punch=1;
				}
			}
		}
	}
}


int main()
{
	int limit;
	char sts[10];
	int typesoftiles=0;
	int alltiles=0;
	int i=1,ij=0,added=0;
	int segcheck=0;
	int equal=0;
	FILE *read;
	char c[1000];
	read = fopen("test.txt","r");
	if (!read)
	return 1;
	while ( fscanf( read, "%s", c )!=EOF)
	{
		fscanf(read,"%[^\n]", c);
		strcpy (sts, c);
		if(quantitycheck(typesoftiles)==0)
		{
			typesoftiles++;
			tile[typesoftiles].segments[0]=sts[0];
			tile[typesoftiles].segments[1]=sts[1];
			tile[typesoftiles].segments[2]=sts[2];
			tile[typesoftiles].segments[3]=sts[3];
			if(sts[4]-'0'==1)
			strcpy (tile[typesoftiles].special,"Temple");
			if(sts[5]-'0'==1)
			strcpy (tile[typesoftiles].special,"Emblem");
			if(sts[4]-'0'==0&&sts[5]-'0'==0)
			strcpy (tile[typesoftiles].special,"Nothing");
			tile[typesoftiles].id=typesoftiles;
			tile[typesoftiles].quantity++;
			added=1;
			alltiles++;
		}
		else
		{
			
			for(i=1;i<=typesoftiles;i++)
			{
				for(ij=0;ij<4;ij++)
				{	
					for(segcheck=0;segcheck<4;segcheck++)
					{
						if(sts[(segcheck+ij)%4]==tile[i].segments[segcheck])
						{
							equal++;
						}
					}
					if(sts[4]-'0'==1&&strcmp(tile[i].special, "Temple")==0)
					{
						equal++;
					}
					if(sts[4]-'0'==0&&sts[5]-'0'==0&&strcmp(tile[i].special, "Nothing")==0)
					{
						equal++;
					}
					if(sts[5]-'0'==1&&strcmp(tile[i].special, "Emblem")==0)
					{
						equal++;
					}
					if(equal==5)
					{
					tile[i].quantity++;
					added=1;
					i=typesoftiles+1;
					alltiles++;
					}
					equal=0;
				}
			}
			if(added==0)
			{
				typesoftiles++;
				tile[typesoftiles].segments[0]=sts[0];
				tile[typesoftiles].segments[1]=sts[1];
				tile[typesoftiles].segments[2]=sts[2];
				tile[typesoftiles].segments[3]=sts[3];
				if(sts[4]-'0'==1)
				strcpy (tile[typesoftiles].special,"Temple");
				if(sts[5]-'0'==1)
				strcpy (tile[typesoftiles].special,"Emblem");
				if(sts[4]-'0'==0&&sts[5]-'0'==0)
				strcpy (tile[typesoftiles].special,"Nothing");
				tile[typesoftiles].id=typesoftiles;
				tile[typesoftiles].quantity++;
				alltiles++;
			}
			added=0;
		}
	}
	fclose(read);
	limit=2*(quantitycheck(typesoftiles)+2);
	int map[limit][limit],j,rot,clear=0,autotileset=0;
	char letter;
	memset(map, 0, sizeof(map[0][0]) * limit * limit);
	int chosen,validity=0;	
	int wish;
	
	yourtiles(typesoftiles);
	printf("Number of tiles left %d\n",quantitycheck(typesoftiles));
	printf("Choose id of the first tile\n");
	scanf("%d", &chosen);
	while(validity==0)
	{
		if(chosen>typesoftiles||chosen<1)
		{
			printf("Wrong id, try again\n");
			scanf("%d", &chosen);
		}
		else
		validity=1;
	}
	rotationchoice(chosen);
	int ITP=quantitycheck(typesoftiles)+1, chosenid=alltiles-quantitycheck(typesoftiles);
	strcpy(tileplaced[chosenid].segments,tile[chosen].segments);
	strcpy(tileplaced[chosenid].special,tile[chosen].special);
	map[ITP][ITP]=chosenid;
	tile[chosen].quantity--;
	tileset(limit,limit,map,typesoftiles);
	printf("\n\n");
	int chosencoord1,chosencoord2;
	while(quantitycheck(typesoftiles)!=0)
	{
		printf("1. Tileset,\n2. Tile list,\n3. Tiles left,\n4. Place a tile,\n5. Score,\n6. Clear console,\n7. Auto-clear (after placing a tile),\n8. Auto-tileset (after placing a tile),\n");
		scanf("%d",&wish);
		switch (wish)
		{
		case 1:
			tileset(limit,limit,map,typesoftiles);
	//		printf("\n\npress any key...\n");
	//		getch();
			break;
		case 2:
			printf("\n");
			yourtiles(typesoftiles);
	//		printf("\npress any key...\n");
	//		getch();
			break;
		case 6:
			system("cls");
			break;
		case 7:
			if(clear==0)
			clear=1;
			else
			clear=0;
			break;
		case 8:
			if(autotileset==0)
			autotileset=1;
			else
			autotileset=0;
			break;
		case 3:
			printf("Number of tiles left %d\n",quantitycheck(typesoftiles));
	//		printf("press any key...\n");
	//		getch();
			break;
		case 4:
			printf("Choose id of a tile\n");
			scanf("%d", &chosen);
			while(validity==0)
			{
				if(chosen>typesoftiles||chosen<1)
				{
					printf("Wrong id, try again\n");
					scanf("%d", &chosen);
				}
				else
				validity=1;
			}
			rotationchoice(chosen);
			printf("Choose coordinates for the tile (x,y) \n");
			scanf("%d,%d", &chosencoord1,&chosencoord2);
			if(ifempty(limit,limit,chosencoord1,chosencoord2,map)!=1)
			{
				printf("There is already a tile at chosen coordinates, try again \n");
				printf("Choose coordinates for the tile (x,y) \n");
				scanf("%d,%d", &chosencoord1,&chosencoord2);
			}
			chosenid=alltiles-quantitycheck(typesoftiles);
			map[chosencoord1][chosencoord2]=chosenid;
			strcpy(tileplaced[chosenid].segments,tile[chosen].segments);
			strcpy(tileplaced[chosenid].special,tile[chosen].special);
			while(placementvalid(limit,limit,chosencoord1,chosencoord2,map)!=1)
			{
				printf("Invalid coordinates, try again \n");
				printf("Choose coordinates for the tile (x,y) \n");
				scanf("%d,%d", &chosencoord1,&chosencoord2);
				map[chosencoord1][chosencoord2]=chosenid;
			}
			tile[chosen].quantity--;
			if(clear==1)
			{
				system("cls");
			}
			if(autotileset==1)
			{
				tileset(limit,limit,map,typesoftiles);
			}
			break;
		}
	}
}
