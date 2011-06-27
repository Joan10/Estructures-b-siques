with d_graf, ada.Integer_Text_IO, ada.Text_IO;
use ada.Integer_Text_IO;

procedure main is



   package dg is new d_graf(8);
   use dg;
   package I_IO is new Ada.Text_IO.Integer_IO (vertex);
   use I_IO;

   g:dg.graf;
   it:dg.iterador;
   v: vertex;

   c: cami;
begin
   dg.gBuit(g);
   dg.primer(g,1,it);

   dg.posaAresta(g,1,2);

    dg.posaAresta(g,2,6);
   dg.posaAresta(g,2,3);
   dg.posaAresta(g,2,4);


   dg.posaAresta(g,3,5);
   dg.posaAresta(g,3,6);

   dg.posaAresta(g,7,2);
   dg.posaAresta(g,8,7);


   dg.primer(g,2,it);

   while dg.valid(it) loop
      dg.getVertex(it,v);
      I_IO.put(v);
      dg.seguent(it);
   end loop;
   ada.Text_IO.new_line;

   dg.cami_mes_llarg(g  => g,
                     v0 => 8,
                     cf => c);

   for y in 1..c.n loop
      I_IO.put(c.v_cami(y));
   end loop;


end main;
