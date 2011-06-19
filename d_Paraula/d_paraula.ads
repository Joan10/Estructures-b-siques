with ada.text_io; use ada.text_IO;
with ada.integer_text_io; use ada.integer_text_IO;
package d_Paraula is

   type Paraula is private;

   procedure Get(P: out Paraula; F: in File_Type);
   procedure Put(P: in Paraula);
   function quedenParaules(F: in file_type) return boolean;

   function charPos(P: in Paraula; Pos: in integer) return character; --funci� que retorna el car�cter de la posici� entrada
   function llargaria(P: in Paraula) return integer; --retorna la llarg�ria de la paraula
private

   MAX: Integer := 50;
   type v_Paraula is array (1..MAX) of character;

   type Paraula is record
      v_p: v_Paraula; --Vector de paraules.
      n: integer;	-- Comptador de car�cters de la paraula.
   end record;

   Paraula_Llarga: exception;

end d_Paraula;
