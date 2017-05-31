    #include <stdio.h>
    #include <limits.h>

    class Point{
    public:
        int related[60];
        unsigned int howManyNeighbours;
        Point(){
            howManyNeighbours=0;
        }
        void addNeigbour(unsigned int value){
            related[howManyNeighbours]=value;
            howManyNeighbours++;
        }
        ~Point(){}
    };

    class Queue{
    public:
        unsigned int howMany;
        int size;
        int *tab;

        Queue(int s){
            howMany=0;
            size=s;
            tab=new int[size];
        }
        void add(int value){
            tab[howMany]=value;
            howMany++;
        }
        void clean(){
            howMany=0;
        }
        ~Queue(){
            delete[]tab;
        }
    };

    class Match{
    public:
        unsigned int people, bikes;
        unsigned int points;
        int *matching, *path;
        Point *graf;
        Queue *Q;
        int tempAmountNeigbours,tempWhichNeigbour,x, matches;
        Match(unsigned int p, unsigned int b): people(p), bikes(b){
            matches=0;
            points=p+b;
            Q=new Queue(points);
            graf=new Point[points+1];
            matching = new int[points];
            path  = new int[points+1];
        }
        ~Match(){
            delete Q;
            delete[]graf;
        }
        bool DFS(int x);
        bool BFS();
        void search();

    };

    void Match::search(){
        for(unsigned int i=1;i<=people;i++){
            scanf("%d", &tempAmountNeigbours);
            for(int j=0;j<tempAmountNeigbours;j++) {
                scanf("%d", &tempWhichNeigbour);
                graf[i].addNeigbour(tempWhichNeigbour+people);
                graf[tempWhichNeigbour+people].addNeigbour(i);
            }
       }

        for(int i = 0; i <= points; i++) {
            matching[i]=0;
        }
        while(BFS()){
            for(int i=1;i<=people;i++){
                if(matching[i]==0)
                    if(DFS(i)){
                    matches++;
                }
            }
        }
        printf("%d",matches);
    }

    bool Match::BFS(){
       Q->clean();
        for(int i=1;i<=people;i++){
            if(matching[i]==0){
                path[i]=0;
                Q->add(i);
            }
            else path[i]=INT_MAX;
        }

        path[0]=INT_MAX;
        int counter=0;

        while(counter!=Q->howMany){

            int x=Q->tab[counter];

            if(path[x]<path[0]){
                for(int i=0;i<graf[x].howManyNeighbours;i++){
                    int y=graf[x].related[i];
                    if(path[matching[y]]==INT_MAX){
                        path[matching[y]]=path[x]+1;
                        Q->add(matching[y]);
                    }

                }
            }
            counter++;
        }
        return(path[0]!=INT_MAX);
    }

    bool Match::DFS(int x){
        if(x!=0) {
            for (int i = 0; i < graf[x].howManyNeighbours; i++) {
                int y = graf[x].related[i];
                if (path[matching[y]] == path[x] + 1) {
                    if (DFS(matching[y]) == true) {
                        matching[y] = x;
                        matching[x] = y;
                        return true;
                    }
                }
            }
            path[x] = INT_MAX;
            return false;
        }
        return true;
    }


    int main() {
        unsigned int bikes, people;
        scanf("%d %d\n", &people, &bikes);
        Match A(people, bikes);
        A.search();
        return 0;
    }