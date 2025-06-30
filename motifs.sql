1) select id from graph1 where v1<v2;

2) select g1.id, g2.id from graph1 g1,graph1 g2 where g1.v2=g2.v1 and g1.v1!=g2.v2 and g1.v1<g1.v2;

3) select g1.id, g2.id, g3.id from graph1 g1,graph1 g2, graph1 g3 where g1.v2=g2.v1 and g2.v2=g3.v1 and g3.v2=g1.v1 and g1.id<g2.id and g2.id<g3.id;

4) select id from graph2;

5) select g1.id, g2.id  from graph2 g1, graph2 g2 where g1.v1=g2.v1 and g1.id!=g2.id;

6) select g1.id, g2.id  from graph2 g1, graph2 g2 where g1.v1=g2.v1 and g1.id<g2.id;

7) select g1.id, g2.id  from graph2 g1, graph2 g2 where g1.v2=g2.v2 and g1.id<g2.id;

8) select g1.id, g2.id, g3.id from graph2 g1, graph2 g2, graph2 g3 where g1.v2=g2.v1 and g2.v2=g3.v1 and g3.v2=g1.v1 and g1.id<g2.id and g1.id<g3.id;

9) select g1.id, g2.id, g3.id from graph2 g1, graph2 g2, graph2 g3 where g1.v1=g2.v1 and g2.v2=g3.v1 and g3.v2=g1.v2;

10) select g1.id, g2.id, g3.id from graph2 g1, graph2 g2, graph2 g3 where g1.v1=g2.v1 and g2.v2=g3.v2 and g3.v1!=g1.v2 and g1.id!=g2.id and g1.id!=g3.id and g2.id!=g3.id;

11) select g1.id, g2.id, g3.id, g4.id from graph2 g1, graph2 g2, graph2 g3, graph2 g4 where g1.v1=g2.v1 and g3.v1=g4.v1 and g1.v2=g3.v2 and g2.v2=g4.v2 and g3.v1!=g1.v2 and g1.id!=g2.id and g1.id!=g3.id and g1.id!=g4.id and g2.id!=g3.id and g2.id!=g4.id and g3.id!=g4.id;

12) select g1.id, g2.id, g3.id from graph2 g1, graph2 g2, graph2 g3 where g1.v2=g2.v1 and g2.v2=g3.v2 and g3.v1!=g1.v1 and g3.id!=g2.id;

13) select g1.id, g2.id, g3.id from graph2 g1, graph2 g2, graph2 g3 where g1.v1=g2.v1 and g2.v2=g3.v1 and g3.id!=g2.id and g1.id!=g2.id and g3.v2!=g1.v2;

14) select g1.id, g2.id, g3.id, g4.id from graph2 g1, graph2 g2, graph2 g3, graph2 g4 where g1.v1=g2.v1 and g3.v2=g4.v2 and g1.v2=g3.v1 and g2.v2=g4.v1 and g1.id!=g2.id and g1.id!=g3.id and g1.id!=g4.id and g2.id!=g3.id and g2.id!=g4.id and g3.id!=g4.id and g1.id<g2.id;
