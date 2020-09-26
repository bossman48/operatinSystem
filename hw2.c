#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
    
typedef struct __node_t {
int size; 
struct __node_t *next;
} node_t;
typedef struct{
  int size;
  int free;//0 is not free 1 is free ;
  struct header_t *next;
  struct header_t *prev;
}header_t;
header_t *firstHeader=NULL;
node_t *head;
node_t *copy;
node_t *copy2;
int sayi=0;
header_t *header48;
void *address;
int InitMyMalloc(int yiginBoyutu){
    if(yiginBoyutu<=0)
        return -1;
        int pageSize=getpagesize();
        int wantedPageSize;
        if(pageSize%yiginBoyutu!=0){
            wantedPageSize=((yiginBoyutu/pageSize)+1)*pageSize;
        }
        else{
            wantedPageSize=yiginBoyutu;
        }
        head = mmap(NULL,
                      wantedPageSize,
                      PROT_READ|PROT_WRITE,
                       MAP_ANON|MAP_PRIVATE,
                      -1,
                      0 );
                      copy2=head;
            head->size =wantedPageSize-sizeof(node_t);
            head->next=NULL;
            
       if ( head != MAP_FAILED ) {
           copy=head;
           return head;
       }
       else
       {
            return -1;
       }
       
        
}   
    void *initAlloc(int boyut){
        int boyut2=checkSize(boyut);
        header_t *header = (header_t*)head;
        header_t *first;
        header_t *last = (header_t*)head;
        int new=head->size -(boyut2+sizeof(header_t));
        int *blockpoint = (int*)head;
        header-> prev = firstHeader;
        firstHeader=(header_t*)blockpoint;
        blockpoint = blockpoint+ (boyut2+sizeof(header_t))/sizeof(int);
        head = (node_t*)blockpoint;
        head -> next =NULL;
        head ->size =new;
        header -> size =boyut2;
        header->next=(header_t*)head;
        header ->free = 0;
        header = header+1;
        sayi++;
        return header;
    }
    void *initAlloc2(header_t *asd,int boyut){
        int *l = (int*) asd ;
        header_t *header =(header_t*)l;
        header_t *k=asd;
        header->size = boyut;
        header->prev=asd->prev;
        header->free=0;
        header->next=asd->next;
       
    }
 
    void *display(){
        header_t *asd=(header_t*) copy;
        printf("Address     Size    State\n");
        while(asd->next!=NULL){
            printf("%d",asd);
            printf("    %d",asd->size);
            if(asd->free==0)
                printf("    Full\n");
            else
            {
                    printf("    Free\n");
            }
            asd=asd->next;
        }
        printf("Address: %d\n",asd);
    }
    int checkSize(int size){
        if(size%8==0){
            return size;
        }
        else{
            int k=size+(8-(size%8));
            return k;
        }
    }
    void *arrangeTheSpace(){
        header_t *asd = (header_t*) head;
        asd -> size = head->size-sizeof(header_t);
        asd ->free = 0;
        asd = asd +1; 
        printf("asd:%d\n",asd);
        head = (node_t*)asd;
        return asd;
    }
    void *firstFit(int boyut){
        header_t *asd=(header_t*)copy;
        while(asd->next != NULL){
            if(asd->size>=boyut+sizeof(header_t) && asd->free == 1){

                asd=initAlloc2(asd,boyut);
                return asd;
            }
            else{
               asd = asd->next;
            }
        }
        printf("There is not suitable space for this size");
        return NULL;
    }

    void *bestFit(int boyut){
        header_t *bestfit=(header_t*) copy;
        int idealSize=10000000;
        while(bestfit->next!=NULL){
            if(bestfit->size>=boyut+sizeof(header_t)){
                if(bestfit->size +sizeof(header_t) < idealSize){
                    idealSize=bestfit->size;
                    }
                    else{
                     bestfit = bestfit->next;
                    }
            }
            else{
               bestfit = bestfit->next;
            }
        }
        bestfit=(header_t*)copy;
        while(bestfit->next!=NULL){
            if(bestfit->size==idealSize){
                return initAlloc2(bestfit,boyut);
            }
            else{
                bestfit=bestfit->next;
            }
        }
    }
    void *worstFit(int boyut){
        header_t *worstfit=(header_t*) copy;
        int idealSize=0;
        while(worstfit->next!=NULL){
            if(worstfit->size>=boyut+sizeof(header_t)){
                if(worstfit->size  > idealSize +sizeof(header_t)){
                    idealSize=worstfit->size;
                    }
                    else{
                     worstfit = worstfit->next;
                    }
            }
            else{
               worstfit = worstfit->next;
            }
        }
        worstfit=(header_t*)copy;
        while(worstfit->next!=NULL){
            if(worstfit->size==idealSize){
                return initAlloc2(worstfit,boyut);
            }
            else{
                worstfit=worstfit->next;
            }
        }
    }

    void *myMalloc(int yontem,int boyut){
        boyut=checkSize(boyut);
        if(yontem == 0){
            //Best Fit
             if(bestFit(boyut)==NULL){
                initAlloc(boyut);
            }
        }
        else if(yontem == 1){
            //Worst Fit
             if(worstFit(boyut)==NULL){
                initAlloc(boyut);
            }
        }
        else if(yontem == 2){
            //First Fit
            if(firstFit(boyut)==NULL){
                initAlloc(boyut);
            }
        }
        else{
            printf("yanlis yontem ");
        }
    }
    void *myFree(void *ptr){
        //printf("ptr:%d\n",(int*)ptr);
        int *asd2=(int*)ptr-sizeof(header_t)/sizeof(int);
        //printf("free:%d\n",asd2);
            if (!ptr) {
        printf("not pointer");
        return NULL;
    }
        header_t *asd=(header_t*) asd2;
        asd->free=1;
        header_t *prev=asd->prev;;
        header_t *next =asd->next;
        header_t *next2 =next->next;
        if(next->free == 1){
            int newSize=asd->size + sizeof(header_t) + next-> size ;
            asd->size = newSize;
            asd->next = next2;
            next2->prev = asd;
        }
        else if(prev->free == 1){
            int newSize=asd->size + sizeof(header_t) + prev -> size ;
            prev->size = newSize;
            prev->next = next;
            next -> prev = prev;
        }
        
    }



int main() {
  printf("initMalloc:%d\n",InitMyMalloc(4096));
  int *a=initAlloc(100);
  int *b=initAlloc(100);
  int *c=initAlloc(400);
  int *d= initAlloc(600);
  int *e=initAlloc(803);
  display();
  myFree(b);
  myFree(e);
  display();
  myMalloc(0,900);
  display();
}