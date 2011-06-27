with ada.Integer_Text_IO; use ada.Integer_Text_IO;
package body d_graf is


   procedure gBuit (g: out graf) is
   begin

      for c in vertex loop
         g(c) := null;
      end loop;

   end gBuit;




   procedure posaAresta (g: in out graf; v1,v2: in vertex) is
      p: pcell;
   begin
      p := new cell; p.all := (v2,g(v1), blanc);
      g(v1) := p;
   end posaAresta;

   procedure treuAresta (g: in out graf; v1,v2: in vertex) is
      p,pp: pcell;
   begin
      pp:=null;
      p:=g(v1);
      while p /= null and then p.x /= v2 loop
         pp:=p;
         p:=p.succ;
      end loop;

      if p = null then raise noExisteix; end if;
      if pp /= null then
         pp.succ := p.succ;
      else
         g(v1) := p.succ;
      end if;


   end treuAresta;


   procedure primer(g: in graf; x: in vertex; it: out iterador) is
   begin
      it.p := g(x);
   end primer;


   procedure seguent(it: in out iterador) is
   begin
      it.p := it.p.succ;
   end seguent;

   function valid(it: in iterador) return boolean is
   begin
      return it.p /= null;
   end valid;

   procedure getVertex(it: in iterador; y: out vertex) is
   begin
      y := it.p.x;
   end getVertex;

   procedure prof0(g: in graf; v: in out vertex; c,cf: in out cami; tc: in out v_color) is
      it: iterador;
      v2: vertex;
   begin
      c.n := c.n +1;  c.v_cami(c.n) := v;
      if c.n > cf.n  then cf := c; end if;
      tc(v) := gris;

      primer(g,v,it);
      while valid(it) loop
         getVertex(it,v2);
         if tc(v2) = blanc then prof0(g,v2,c,cf,tc);
         elsif tc(v2) = gris then raise esCiclic;
         end if;
         seguent(it);
      end loop;

      tc(v) := negre;
      c.n := c.n - 1 ;
   end prof0;

   procedure cami_mes_llarg (g: in graf; v0: in vertex; cf: out cami) is
      c: cami;
      v:vertex:=v0;
      tc : v_color;
   begin

      for i in vertex loop
         tc(i) := blanc;
      end loop;

      prof0(g, v, c, cf, tc);
   end cami_mes_llarg;

end d_graf;
