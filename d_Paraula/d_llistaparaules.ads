with d_paraula, ada.integer_text_io, ada.text_io;
use d_paraula, ada.integer_text_io, ada.text_io;
package d_llistaparaules is

   type LlistaParaules is private;

   type e_Ordre is (Ascendent, Descendent);

   procedure LlistaBuida(L: out LlistaParaules);
   --Retorna una llista buida.

   procedure Posa(L: in out LlistaParaules; P: in Paraula);
   --Posa un element a la llista. (una paraula)

   procedure Ordena(L: in out LlistaParaules);
   --Ordena una llista per l'algoritme de binsort

   procedure Escriu(L: in LlistaParaules; E: e_Ordre);
   --Escriu per pantalla una llista en un ordre determinat (ascendent, descendent)

   function esBuida(L: in LlistaParaules) return boolean;
   --Retorna cert si la llista és buida.

private

   type nLlista;
   --declaració anticipada node llista

   type Ptr_nLlista is access nLLista;
   --Punter a node llista.

   type LlistaParaules is record
   --tipus abstracte llista de paraules
      Primer, Darrer: Ptr_nLlista;
   end record;

   type nLlista is record
   --tipus abstracte d'un node de la llista.
      succ,pred: Ptr_nLlista;
      P: d_Paraula.Paraula;
   end record;

   error_LlistaBuida: exception;

end d_LlistaParaules;
