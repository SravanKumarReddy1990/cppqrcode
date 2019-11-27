#include <stdio.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>

void do_exit(PGconn *conn) {
    
    PQfinish(conn);
    exit(1);
}
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)  + strlen(s2) + 1); 
    // in real code you would check for errors in malloc here
    strcpy(result, s1); 
    strcat(result, s2);
    return result;
}
int mains(char *id, char *password) {
    
    PGconn *conn = PQconnectdb("user=postgres host=localhost password=postgres dbname=postgres");

    if (PQstatus(conn) == CONNECTION_BAD) {
        
        fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
        do_exit(conn);
    }
char *select="SELECT * FROM users";
char *where=concat(select," where username='");
char *idval=concat(where,id);
char *idvalclose=concat(idval,"' and password='");
char *passval=concat(idvalclose,password);
char *passvalclose=concat(passval,"' and enabled='t'");
printf(passvalclose);
    PGresult *res = PQexec(conn, passvalclose);    
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {

        printf("\nNo data retrieved\n");        
        PQclear(res);
        do_exit(conn);
return 0;
    }    
    
    int rows = PQntuples(res);
    
    for(int i=0; i<rows; i++) {
        
        printf("\n %s %s %s\n", PQgetvalue(res, i, 0), 
            PQgetvalue(res, i, 1), PQgetvalue(res, i, 2));
return 1;
    }    

    PQclear(res);
    PQfinish(conn);

    return 0;
}
