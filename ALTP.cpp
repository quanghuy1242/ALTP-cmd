#include <conio.h> 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
struct console{ //ham sua console
	console( unsigned width, unsigned height ){
		SMALL_RECT r;
    	COORD      c;
    	hConOut = GetStdHandle( STD_OUTPUT_HANDLE );
	
    	r.Left   =
    	r.Top    = 0;
   	 	r.Right  = width -1;
   	 	r.Bottom = height -1;
    SetConsoleWindowInfo( hConOut, TRUE, &r );
	c.X = width;
    c.Y = height;
    SetConsoleScreenBufferSize( hConOut, c );
    }

	HANDLE hConOut;	
	CONSOLE_SCREEN_BUFFER_INFO csbi;
};
struct cauhoi{
	int ma,sott;
	char q[1000], da1[100], da2[100], da3[100], da4[100], kq[2];
};
struct Node{
	cauhoi data;
	Node *link;
};
struct List{
	Node *first, *last;
};
void init(List &l){
	l.first=l.last=NULL;
}
Node *GetNode(cauhoi s){
	Node *p=new Node;
	if(p==NULL) return NULL;
	p->data=s;
	p->link=NULL;
	return p;
}
void AddLast(List &l, Node *p){
	if(!l.first){
		l.first=l.last=p;
	}else{
		l.last->link=p;
		l.last=p;
	}
}
void InsertLast(List &l, cauhoi	s){
	Node *p=GetNode(s);
	if(p==NULL) return;
	AddLast(l,p);
}
void TextColor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}
void Danhsachcauhoi(List &l, FILE *f){
	cauhoi s; char temp[2];
	if(!f) printf("Khong mo duoc.");
	while(!feof(f)&&f!=NULL){
		fscanf(f,"%d",&s.ma);
		fgets(temp,2,f);
		fgets(s.q,1000,f);
		fgets(s.da1,1000,f);
		fgets(s.da2,1000,f);
		fgets(s.da3,1000,f);
		fgets(s.da4,1000,f);
		fgets(s.kq,2,f);
		fgets(temp,2,f);
		InsertLast(l,s);
	};
}
void Xoatoanbodscauhoi(List &l){
	Node *p;
	while(l.first){
		p=l.first;
		l.first=p->link;
		delete(p);
	}
	l.last=NULL;
}
void themcauhoi(List &l){
	cauhoi moi;
	char traloi[1000], c[]="\n";
	moi.ma=l.last->data.ma+1; 
	strcpy(moi.da1,"A. "); strcpy(moi.da2,"B. "); strcpy(moi.da3,"C. "); strcpy(moi.da4,"D. ");
	TextColor(14);
	printf("\n\tCau hoi: "); TextColor(15); gets(moi.q); strcat(moi.q,c);
	printf("\t\tA. "); gets(traloi);  strcat(moi.da1,traloi); strcat(moi.da1,c);
	printf("\t\tB. "); gets(traloi);  strcat(moi.da2,traloi); strcat(moi.da2,c);
	printf("\t\tC. "); gets(traloi);  strcat(moi.da3,traloi); strcat(moi.da3,c);
	printf("\t\tD. "); gets(traloi);  strcat(moi.da4,traloi); strcat(moi.da4,c);
	TextColor(14); printf("\t >>>Dap an dung: "); TextColor(15); gets(moi.kq);
	InsertLast(l,moi);
}
int Timkiemcauhoi(List l, int x){
	Node *p=l.first;
	while(p){
		if(p->data.ma==x){
			printf("   %s",p->data.q);
			printf("\t%s",p->data.da1);
			printf("\t%s",p->data.da2);
			printf("\t%s",p->data.da3);
			printf("\t%s",p->data.da4);
			printf(" >>>Dap an dung: %s",p->data.kq);
			return p->data.ma;
		}
		p=p->link;
	}
	return -1;
}
int TimPhanTu(int a[], int n, int x){
	int i;
	if(n==0) return 0;
	for(i=0; i<n; i++)
		if(a[i] == x) return 1;
	return 0;
}
void gen_random(int a[],int n)
{ 
	srand(time(NULL));
    int i,x;
    x=rand()%n-1; 
	
    for(i=0;i<n;i++) 
    {
  		while(TimPhanTu(a,i,x)) 
            x=rand()%n;
        a[i]=x;
    } 
}
void ramdomthutulist(List &l, int a[]){
	Node *p=l.first;
	int i=0;
	while(p && i<=101){
 		p->data.sott=a[i];
		i++;
		p=p->link;
	}
}
void sapxep(List &l){
	for(Node *p=l.first;p!=l.last;p=p->link)
		for(Node *q=p->link;q!=NULL;q=q->link)
			if(p->data.sott>q->data.sott){
				cauhoi tt=p->data;
				p->data=q->data;
				q->data=tt;
			}
}
void xuattrogiup(int a[]){
	if(a[0]==1){
		TextColor(207); printf("[1:50/50]"); TextColor(15);
	}else{
		TextColor(204); printf("[1:50/50]"); TextColor(15);
	}
	if(a[1]==2){
		TextColor(207); printf("[2:Chuyen gia tu van]"); TextColor(15);
	}else{
		TextColor(204); printf("[2:Chuyen gia tu van]"); TextColor(15);
	}
	if(a[2]==3){
		TextColor(207); printf("[3:Y kien khan gia]    "); TextColor(15);
	}else{
		TextColor(204); printf("[3:Y kien khan gia]    "); TextColor(15);
	}
	printf("\n");
}
void Xuatcauhoi(cauhoi s, int a[],int b[], int tt){
	printf("\t"); TextColor(207);
	printf("===========================================================================\n");
	TextColor(15); printf("\t"); TextColor(207);
	printf("    [X:Dung cuoc choi]"); xuattrogiup(a);
	TextColor(15); printf("\t"); TextColor(207);
	TextColor(207);
	printf("===========================================================================\n");
	
	
	TextColor(12);
	printf("\t\t\t===================================\n");
	printf("\t\t\t\t  CAU HOI SO %d: \n",tt);
	printf("\t\t\t\t ===============\n");
	TextColor(11);
	printf("%s\n",s.q);
	TextColor(15);
	
		if(b[0]==1) printf("	  %s",s.da1);
		else{
			TextColor(256); printf("	  %s",s.da1); TextColor(15);
		}
		if(b[1]==1 ) printf("	  %s",s.da2);
			else{
				TextColor(256); printf("	  %s",s.da2); TextColor(15);
		}
		if(b[2]==1 ) printf("	  %s",s.da3);
			else{
				TextColor(256); printf("	  %s",s.da3); TextColor(15);
		}
		if(b[3]==1 ) printf("	  %s",s.da4);
			else{
				TextColor(256); printf("	  %s",s.da4); TextColor(15);
		}
}
long diem(int x){
	switch(x){
		case 0: return 0;
		case 1: return 200;
		case 2: return 400;
		case 3: return 600;
		case 4: return 1000;
		case 5: return 2000;
		case 6: return 3000;
		case 7: return 6000;
		case 8: return 10000;
		case 9: return 14000;
		case 10: return 22000;
		case 11: return 30000;
		case 12: return 40000;
		case 13: return 60000;
		case 14: return 85000;
		case 15: return 150000;
	}
}
long KTdiem(int a){
	long x=diem(a);
	if(x<2000) return 0;
	if(x>=2000 && x<22000) return 2000;
	if(x>=22000 && x<150000) return 22000;
	if(x==150000) return 150000;
	
}
int Timmin(long a[]){
	long minn=a[0];
	for(int i=0;i<10;i++)
		if(a[i]<minn){
			minn=a[i];
		}
	return minn;
}
void HoanVi(long &x, long &y)
{
	long q=x;
	x=y;
	y=q;
}
void ykienkhangia(int x, int y, int z, int t){
	printf("\n\tCo %2d%% khan gia chon phuong an A\n",x);
	printf("\tCo %2d%% khan gia chon phuong an B\n",y);
	printf("\tCo %2d%% khan gia chon phuong an C\n",z);
	printf("\tCo %2d%% khan gia chon phuong an D\n",t);
}
int Kiemtradapan(char a[]){
	char b=a[0];
	switch(b){
		case 'A': return 1;
		case 'B': return 1;
		case 'C': return 1;
		case 'D': return 1;
		case 'X': return 1;
		case 'a': return 1;
		case 'b': return 1;
		case 'c': return 1;
		case 'd': return 1;
		case 'x': return 1;
		case '1': return 1;
		case '2': return 1;
		case '3': return 1;
	}
	return 0;
}
void XoaPhanTu(int a[], int x)
{
	for(int i=0;i<3;i++)
		if(a[i]==x) a[i]=0;	
}
void Chuongtrinh(List l, long &b,int vvv){
	Node *p=l.first;
	char traloi[2], alarm[2], chon[2];
	int socau=0, trogiup[4]={1,2,3},c[5]={1,1,1,1},thutu2[vvv],tt=1,tl=0; long cc=0;
	gen_random(thutu2,vvv);
	ramdomthutulist(l,thutu2);
	sapxep(l);
	while(p && socau<15){
		Xuatcauhoi(p->data,trogiup,c,tt);
		printf("\n  >>> ");
		TextColor(12);
		printf("Dap an hoac chon tro giup: "); TextColor(15);
		do{
			gets(traloi);
			if(!Kiemtradapan(traloi)){
				printf("\n   Du lieu sai, nhap lai: ");
			}
		}while(!Kiemtradapan(traloi));
			if(strcmpi(p->data.kq,traloi)==0){
			printf("\n	                \t>>>Dap an DUNG.\n");
			socau++; tt++;
			printf("\n\t	      \tChuc mung ban vuot qua cau hoi nay.\n");
			TextColor(12);
			printf("	   \t	================================\n");
			printf("	   \t	||  Ban dang co: %5ld diem   ||\n",diem(socau));
			printf("	   \t	================================");
			TextColor(15);
			Sleep(1000);
			system("cls");
		} 
		else if(strcmpi(traloi,"X")==0){
				printf("Ban da dung cuoc choi!!!\n");
				tl=1;
				cc=diem(socau);
				break;
				}
				else if(strcmpi(traloi,"2")==0){
					if(TimPhanTu(trogiup,3,2)==1){
						printf("\n\t\t     Chuyen gia tu van cho ban %s\n",p->data.kq);
						XoaPhanTu(trogiup,2);
						//socau++; 
						printf("\nNhan bat ki de tiep tuc . . . "); gets(alarm); 
						system("cls");
						continue;
					}else{
						printf("\n\t\t     Ban da su dung quyen tro giup nay roi.\n");
						printf("\nNhan bat ki de tiep tuc . . . "); gets(alarm); 
						system("cls");
						continue;
					} 
					
				}
				else if(strcmpi(traloi,"3")==0){
					if(TimPhanTu(trogiup,3,3)==1){
						srand(time(NULL));
						int x=rand()%20, y=rand()%25, z=rand()%10;
						int t=100-x-y-z; 
						if(strcmpi(p->data.kq,"A")==0) 
							ykienkhangia(t,y,z,x);
						if(strcmpi(p->data.kq,"B")==0) 
							ykienkhangia(y,t,z,x);
						if(strcmpi(p->data.kq,"C")==0) 
							ykienkhangia(z,y,t,x);
						if(strcmpi(p->data.kq,"D")==0) 
							ykienkhangia(x,y,z,t);
						XoaPhanTu(trogiup,3);
						//socau++;
						printf("\nNhan bat ki de tiep tuc . . . "); gets(alarm); 
						system("cls");
						continue;
					}else{
						printf("\n\t\t     Ban da su dung quyen tro giup nay roi.\n");
						printf("\nNhan bat ki de tiep tuc . . . "); gets(alarm); 
						system("cls");
						continue;
					} 
					
				}
				else if(strcmpi(traloi,"1")==0){
					if(TimPhanTu(trogiup,3,1)==1){
						if(strcmpi(p->data.kq,"A")==0){c[1]=0; c[3]=0;}
						if(strcmpi(p->data.kq,"B")==0){c[0]=0; c[2]=0;}
						if(strcmpi(p->data.kq,"C")==0){c[0]=0; c[1]=0;}
						if(strcmpi(p->data.kq,"D")==0){c[2]=0; c[0]=0;}
						XoaPhanTu(trogiup,1);
						//socau++;
						system("cls");
						continue;
					}
					else{
						printf("\n\t\t     Ban da su dung quyen tro giup nay roi.\n");
						printf("\nNhan bat ki de tiep tuc . . . "); gets(alarm); 
						system("cls");
						continue;
					} 
					
				}
			else{
				printf("\n\t\t\t\t   >>>Dap an SAI.\n");
				printf("\n\t\t\t\tCau tra loi dung la: %s\n",p->data.kq);
				break;
			}
			//Dat cac tro giup ve ban dau
			for(int i=0;i<4;i++) c[i]=1;
		p=p->link;
	}
	TextColor(12);
	printf("\t\t\t\t     =========\n");
	printf("\t\t\t\t ===[GAME OVER]===\n");
	printf("\t\t\t\t     =========\n");
	TextColor(14);
	if(tl==1){
		printf("\t\t\t\t  KET THUC: %5ld\n",cc);
		b=cc;
	} 
	else{
		printf("\t\t\t\t  KET THUC: %5ld\n",KTdiem(socau));
		b=KTdiem(socau);
	} 
	
	TextColor(15);
	printf("\n\tNhan bat ki de quay ve man hinh lua chon . . . "); gets(alarm); system("cls");
}
void intro(){
	char t[2];
	TextColor(12);
	printf("					 =========\n");
	printf("				   	[HUONG DAN]\n");
	printf("					 =========\n");
	TextColor(15);
	printf("- Nguoi choi chinh phai vuot qua 15 cau hoi voi muc do tu de toi kho.\n");
	printf("- Khi qua duoc 3 moc 5, 10, 15 thi ban se co chan chan diem cua coc moc do.\n");
	printf("- Co cac quyen tro giup la: +  50:50\n");
	printf("                            +  tu van chuyen gia\n");
	printf("                            +  hoi y kien khan gia truong quay\n");
	printf("- LUU Y: + Neu nguoi choi muon dung cuoc choi, hay nhap X trong luc chon dap an!!!\n");
	printf("         + Ban co the nhap 1, 2, 3 trong luc chon dap an de su dung cac tro giup.\n");
	printf("\n- Neu co loi \"Du lieu sai, nhap lai\", co le ban da bam lung tung luc chay CT\n");
	TextColor(14);
	printf("\n				!!!Chuc ban may man!!!\n\n");
	TextColor(15);
	printf("Nhan enter de xem chi tiet >>> "); gets(t);
	system("cls");
}
void cacmocdiem(){
	char t[2];
	printf("\n[X:Dung cuoc choi][1:50/50][2:Chuyen gia tu van][3:Y kien khan gia]\n\n");
	printf("\tCac moc diem cu the nhu sau: \n\n");
	TextColor(14);
	printf("\t\t15. 150000\n");
	TextColor(15);
	printf("\t\t 14. 85000\n");
	printf("\t\t 13. 60000\n");
	printf("\t\t 12. 40000\n");
	printf("\t\t 11. 30000\n");
	TextColor(14);
	printf("\t\t10. 22000\n");
	TextColor(15);
	printf("\t\t 09. 14000\n");
	printf("\t\t 08. 10000\n");
	printf("\t\t 07. 6000\n");
	printf("\t\t 06. 3000\n");
	TextColor(14);
	printf("\t\t05. 2000\n");
	TextColor(15);
	printf("\t\t 04. 1000\n");
	printf("\t\t 03. 600\n");
	printf("\t\t 02. 400\n");
	printf("\t\t 01. 200\n");
	printf("\n\tNhan bat ki de tiep tuc . . . "); gets(t); system("cls");
	
}
void menu(){
	printf("\t\t\t1. Choi\n");
	printf("\t\t\t2. Huong dan\n");
	printf("\t\t\t3. Diem cao\n");
	printf("\t\t\t4. Them cau hoi moi\n");
	printf("\t\t\t5. Tim kiem cau hoi\n");
	printf("\t\t\t6. Cap nhat du lieu voi cau hoi moi\n");
	printf("\t\t\t7. Dat lai du lieu ve ban dau\n");
	printf("\t\t\t8. Thong tin chuong trinh\n");
	printf("\t\t\t9. Thoat\n");
}
void luudiemcao(long a[]){
	FILE* e=fopen("diemcao.txt","w");
	for(int i=0;i<10;i++)
		fprintf(e,"%ld\t",a[i]);
	fclose(e);
}
void docdiemcao(long a[]){
	FILE* e=fopen("diemcao.txt","r");
	int i=0;
	while(!feof(e)){
		fscanf(e,"%ld",&a[i]);
		i++;
	}
}
void SapXepAmGiamDan(long a[], int n)
{
	int i, j;
	for(i=0; i<n-1; i++) 
		for(j=i+1; j<n; j++) 
			if(a[j]>a[i]) 
				HoanVi(a[i], a[j]);	
	
} 
void about(){
	TextColor(12);
	printf("\n\n\t================THONG TIN CHUONG TRINH====================\n\n");
	TextColor(15);
	printf("\tChuong trinh duoc phat trien boi Nguyen Quang Huy,Do Minh Hau\n");
	TextColor(15);
}
void Capnhatdulieu(List &l, int key){
	cauhoi moi;
	char traloi[1000], c[]="\n"; 
	strcpy(moi.da1,"A. "); strcpy(moi.da2,"B. "); strcpy(moi.da3,"C. "); strcpy(moi.da4,"D. ");
	printf("\nCau hoi: "); gets(moi.q); strcat(moi.q,c);
	printf("\tA. "); gets(traloi);  strcat(moi.da1,traloi); strcat(moi.da1,c);
	printf("\tB. "); gets(traloi);  strcat(moi.da2,traloi); strcat(moi.da2,c);
	printf("\tC. "); gets(traloi);  strcat(moi.da3,traloi); strcat(moi.da3,c);
	printf("\tD. "); gets(traloi);  strcat(moi.da4,traloi); strcat(moi.da4,c);
	printf(" >>>Dap an dung(A,B,C,D): "); do{
		gets(moi.kq);
		if(strlen(moi.kq)>1) printf("Dap an chi co mot ki tu!!!, Nhap lai: ");
	}while(strlen(moi.kq)!=1);
	
	
	Node *p=l.first;
						while(p){
							if(p->data.ma==key){
								strcpy(p->data.q,moi.q);
								strcpy(p->data.da1,moi.da1);
								strcpy(p->data.da2,moi.da2);
								strcpy(p->data.da3,moi.da3);
								strcpy(p->data.da4,moi.da4);
								strcpy(p->data.kq,moi.kq);
							}
							p=p->link;
						}
	
	p=GetNode(moi);
}

void ghidulieu(List l){
	FILE* e=fopen("text.txt","w");
	Node *p=l.first;
	while(p!=l.last){
		fprintf(e,"%d\n",p->data.ma);
		fprintf(e,"%s",p->data.q); 
		fprintf(e,"%s",p->data.da1);
		fprintf(e,"%s",p->data.da2); 
		fprintf(e,"%s",p->data.da3); 
		fprintf(e,"%s",p->data.da4); 
		fprintf(e,"%s\n",p->data.kq);
		p=p->link;
	}
		
		fprintf(e,"%d\n",l.last->data.ma);
		fprintf(e,"%s",l.last->data.q); 
		fprintf(e,"%s",l.last->data.da1);
		fprintf(e,"%s",l.last->data.da2); 
		fprintf(e,"%s",l.last->data.da3); 
		fprintf(e,"%s",l.last->data.da4); 
		fprintf(e,"%s",l.last->data.kq);
	fclose(e);
}
int main(){
	console con( 98, 30 );
	List l; char temp[2]; int chon, i=0, vvv=100;
	long a[11], b=0;
	FILE* f=fopen("text.txt","r");
	srand(time(NULL));
	init(l);
	Danhsachcauhoi(l,f);
	fflush(stdin);
	docdiemcao(a);
	do{
		TextColor(207);
		printf("		=================================================================	  	 \n");
		printf("			CHAO MUNG BAN DEN VOI CHUONG TRINH AI LA TRIEU PHU    		  	 \n");
		printf("		=================================================================  		 \n\n");
		TextColor(15);
		menu();
		TextColor(14);
		printf("\t\t\t      >>>Lua chon: "); TextColor(15); 
			scanf("%d",&chon); fflush(stdin);
		TextColor(15);
		switch(chon){
			case 1:
			{
				system("cls");
				TextColor(15);
				intro();
				cacmocdiem();
				printf("\n\n\t\tHAY BAT DAU DI TIM AI LA TRIEU PHU!!!\n");
				gets(temp); system("cls");
				Chuongtrinh(l,b,vvv);
				if(b>Timmin(a)){
					for(int j=0;j<10;j++)
						if(a[j]==Timmin(a)){
							a[j]=b; break;
						}
				}
				luudiemcao(a);
				fclose(f);
			} break;
			case 2:{
				system("cls");
				intro();
				cacmocdiem();
			} break;
			case 3:{
				system("cls");
				docdiemcao(a);
				SapXepAmGiamDan(a,10);
				TextColor(12);
				printf("\n\n\t\t========================DIEM CAO==========================\n\n");
				TextColor(15);
				printf("\t\t(Luu y: Diem cao se khong bi reset sau khi thoat chuong trinh)\n\n");
				TextColor(14);
				printf("\t\t\t\t1. %d\n",a[0]);
				TextColor(15);
				for(int j=1;j<10;j++)
					printf("\t\t\t\t%d. %d\n",j+1,a[j]);
				TextColor(12);
				printf("\n\t\t==========================================================\n");
				TextColor(15);
				printf("\n\n\tDat lai diem cao nhan 1, de thoat nhan nhan bat ki: "); int chondl; scanf("%d",&chondl);
				fflush(stdin);
				if(chondl==1){
					for(int i=0;i<10;i++)
						a[i]=0;
					printf("\tThanh cong!!!"); Sleep(1000);
				}else{
					luudiemcao(a);
					system("cls");
				}
			}break;
			case 8:{
				
				system("cls");
				about();
				printf("\n\tNhan bat ki de quay ve man hinh lua chon . . . "); gets(temp);
				system("cls");
			}break;
			case 4:{
				system("cls");
				TextColor(12);
				printf("\n\n\t\t=======================BO SUNG CAU HOI=======================\n\n");
				TextColor(15);
				themcauhoi(l);
				ghidulieu(l);
				TextColor(12);
				printf("\n\tDu lieu duoc cap nhat!!! "); TextColor(15);
				printf("\n\n\tNhan bat ki de quay ve man hinh lua chon . . . "); gets(temp);
				system("cls");
			}break;
			case 6:{
				int ma,key; char luachon[0];
				system("cls");
				TextColor(12);
				printf("\n\n\t\t=======================CAP NHAT CAU HOI=======================\n\n");
				TextColor(14);
				printf("Nhap ma so cau hoi can cap nhat: "); TextColor(15); scanf("%d",&ma); fflush(stdin);
				printf("\n");
				key=Timkiemcauhoi(l,ma);
				if(key==-1){
					printf("Khong tim thay.");
					printf("\n\n\tNhan bat ki de quay ve man hinh lua chon . . . "); gets(temp);
					system("cls");  break;
				} 
				TextColor(14);
				printf("\n\n\tBan co muon cap nhat cau hoi nay khong?(Y/N): ");
				TextColor(15); gets(luachon);
				if(strcmpi(luachon,"Y")){
					printf("\n\n\tNhan bat ki de quay ve man hinh lua chon . . . "); gets(temp);
					system("cls");  break;
				}else{
					Capnhatdulieu(l,key);
					ghidulieu(l);
					TextColor(14);
					printf("\n\tDu lieu da duoc cap nhat!!!");
					TextColor(15);
					}
				
				printf("\n\n\tNhan bat ki de quay ve man hinh lua chon . . . "); gets(temp);
				system("cls");
			} break;
			case 5:{
				int ma;
				system("cls");
				TextColor(12);
				printf("\n\n\t\t=======================TIM KIEM CAU HOI=======================\n\n");
				TextColor(14);
				printf("Nhap ma so cau hoi can tim kiem: "); TextColor(15); scanf("%d",&ma); fflush(stdin);
				printf("\n");
				int keyy=Timkiemcauhoi(l,ma);
				if(keyy==-1){
					printf("Khong tim thay.");
					printf("\n\n\tNhan enter de quay ve man hinh lua chon . . . "); gets(temp);
					system("cls");  break;
				} 
				printf("\n\n\tNhan bat ki de quay ve man hinh lua chon . . . "); gets(temp);
				system("cls");
			} break;
			case 7:{
				system("cls");
				Xoatoanbodscauhoi(l);
				FILE* dd=fopen("restore.txt","r");
				Danhsachcauhoi(l,dd);
				fclose(dd);
				TextColor(14);
				printf("\n\tDu lieu da duoc dat lai!!!");
				TextColor(15);
				ghidulieu(l);
				printf("\n\n\tNhan bat ki de quay ve man hinh lua chon . . . "); gets(temp);
				system("cls");
			} break;
			case 9: exit(1);
			default:{
				printf("\t\tKhong co chuc nang nay!!! ");
				Sleep(1000);
				system("cls");
				break;
			}
		}
	}while(chon!=9);
	return 0;
}
