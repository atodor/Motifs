#define Q1 "select id from %s where v1<v2;"

#define Q2 "select g1.id, g2.id from %s g1,%s g2 where g1.v2=g2.v1 and g1.v1!=g2.v2 and g1.id<g2.id;"

#define Q3 "select g1.id, g2.id, g3.id from %s g1, %s g2, %s g3 where g1.v2=g2.v1 and g2.v2=g3.v1 and g3.v2=g1.v1 and g1.id<g2.id and g2.id<g3.id;"

#define Q4 "select id from %s;"

#define Q5 "select g1.id, g2.id from %s g1, %s g2 where g1.v2=g2.v1 and g1.v1!=g2.v2;"

#define Q6 "select g1.id, g2.id from %s g1, %s g2 where g1.v1=g2.v1 and g1.id<g2.id and g1.v2!=g2.v2;"

#define Q7 "select g1.id, g2.id from %s g1, %s g2 where g1.v2=g2.v2 and g1.id<g2.id and g1.v1!=g2.v1;"

#define Q8 "select g1.id, g2.id, g3.id from %s g1, %s g2, %s g3 where g1.v2=g2.v1 and g2.v2=g3.v1 and g3.v2=g1.v1 and g1.id<g2.id and g1.id<g3.id;"

#define Q9 "select g1.id, g2.id, g3.id from %s g1, %s g2, %s g3 where g1.v1=g2.v1 and g2.v2=g3.v1 and g3.v2=g1.v2;"

#define Q10 "select g1.id, g2.id, g3.id from %s g1, %s g2, %s g3 where g1.v1=g2.v1 and g2.v2=g3.v2 and g3.v1!=g1.v2 and g1.id!=g2.id and g1.id!=g3.id and g2.id!=g3.id and g1.v2!=g2.v2;"

#define Q11 "select g1.id, g2.id, g3.id, g4.id from %s g1, %s g2, %s g3, %s g4 where g1.v1=g2.v1 and g3.v1=g4.v1 and g1.v2=g3.v2 and g2.v2=g4.v2 and g3.v1!=g1.v2 and g2.v1!=g4.v2 and g1.id<g2.id and g3.id<g4.id and g1.id<g3.id and g1.v1!=g3.v1 and g1.v2!=g2.v2;"

#define Q12 "select g1.id, g2.id, g3.id from %s g1, %s g2, %s g3 where g1.v2=g2.v1 and g2.v2=g3.v2 and g3.v1!=g1.v1 and g3.id!=g2.id and g2.v2!=g1.v1;"

#define Q13 "select g1.id, g2.id, g3.id from %s g1, %s g2, %s g3 where g1.v1=g2.v1 and g2.v2=g3.v1 and g3.v2!=g1.v2 and g2.v2!=g1.v2 and g3.v2!=g2.v1;"

#define Q14 "select g1.id, g2.id, g3.id, g4.id from %s g1, %s g2, %s g3, %s g4 where g1.v1=g2.v1 and g3.v2=g4.v2 and g1.v2=g3.v1 and g2.v2=g4.v1 and g1.id!=g3.id and g1.id!=g4.id and g2.id!=g3.id and g2.id!=g4.id and g3.id!=g4.id and g1.id<g2.id and g2.v2!=g1.v1;"

#define Q15 "select g1.id, g2.id, g3.id from %s g1, %s g2, %s g3 where g1.v2=g2.v2 and g1.v2=g3.v1 and g1.id<g2.id and g2.id<g3.id;"

#define Q16 "select g1.id, g2.id, g3.id from %s g1, %s g2, %s g3 where g1.v2=g2.v1 and g2.v2=g3.v1 and g1.id!=g2.id and g1.id!=g3.id and g2.id!=g3.id and g1.v1!=g3.v2;"

#define Q17 "select g1.id, g2.id, g3.id from %s g1, %s g2, %s g3 where g1.v1=g2.v1 and g1.v1=g3.v1 and g1.id<g2.id and g1.id<g3.id and g2.id<g3.id;"

#define Q18 "select g1.id, g2.id, g3.id from %s g1, %s g2, %s g3 where g1.v2=g2.v2 and g1.v2=g3.v2 and g1.id<g2.id and g1.id<g3.id and g2.id<g3.id;"

#define Q19 "select g1.id, g2.id, g3.id from %s g1, %s g2, %s g3 where g1.v2=g2.v2 and g1.v2=g3.v1 and g1.id<g2.id and g1.id!=g3.id and g2.id!=g3.id;"

#define Q20 "select g1.id, g2.id, g3.id from %s g1, %s g2, %s g3 where g1.v1=g2.v1 and g1.v1=g3.v2 and g1.id<g2.id and g1.id!=g3.id and g2.id!=g3.id;"

#define Q21 "select g1.id, g2.id, g3.id from %s g1, %s g2, %s g3 where g1.v2=g2.v1 and g2.v2=g3.v1 and g1.v1!=g3.v2;"

