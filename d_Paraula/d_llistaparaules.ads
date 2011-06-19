with d_paraula, ada.integer_text_io, ada.text_io;
use d_paraula, ada.integer_text_io, ada.text_io;
package d_llistaparaules is

   type LlistaParaules is private;

   type e_Ordre is (Ascendent, Descendent);

   procedure LlistaBuida(L: out LlistaParaules);
   procedure Posa(L: in out LlistaParaules; P: in Paraula);
   procedure Ordena(L: in out LlistaParaules);
   procedure Escriu(L: in LlistaParaules; E: e_Ordre);

   function esBuida(L: in LlistaParaules) return boolean;

private

   type nLlista;

   type Ptr_nLlista is access nLLista;

   type LlistaParaules is record
      Primer, Darrer: Ptr_nLlista;
   end record;

   type nLlista is record
      succ,pred: Ptr_nLlista;
      P: d_Paraula.Paraula;
   end record;



   error_LlistaBuida: exception;

end d_LlistaParaules;
