generic
nv: positive;

package d_graf is
   type vertex is new integer range 1..nv;
   type graf is private;
   type iterador is private;

   type dv_cami is array (1..nv) of vertex;
   type cami is record
      v_cami: dv_cami;
      n: integer := 0;
   end record;

   procedure gBuit (g: out graf);
   procedure posaAresta (g: in out graf; v1,v2: in vertex);
   procedure treuAresta (g: in out graf; v1,v2: in vertex);

   procedure primer(g: in graf; x: in vertex; it: out iterador);
   procedure seguent(it: in out iterador);
   function valid(it: in iterador) return boolean;
   procedure getVertex(it: in iterador; y: out vertex);
   procedure cami_mes_llarg (g: in graf; v0: in vertex; cf: out cami);
   type color is (blanc, gris, negre);

   noExisteix: exception;
   esCiclic: exception;



private
   type v_color is array (vertex) of color;

   type cell;
   type pcell is access cell;

   type cell is record
      x: vertex;
      succ: pcell;
      c: color;
   end record;

   type graf is array (vertex) of pcell;

   type iterador is record
      p: pcell;
   end record;


end d_graf;
