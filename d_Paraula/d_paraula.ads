with ada.text_io; use ada.text_IO;
with ada.integer_text_io; use ada.integer_text_IO;
package d_Paraula is

   type Paraula is private;

   procedure Get(P: out Paraula; F: in File_Type); --Get d'una paraula des d'un fitxer.
   procedure Put(P: in Paraula); --Imprimeix per pantalla una paraula.
   function quedenParaules(F: in file_type) return boolean; --Retorna cert si queden paraules al fitxer.

   function charPos(P: in Paraula; Pos: in integer) return character; --funció que retorna el caràcter de la posició entrada
   function llargaria(P: in Paraula) return integer; --retorna la llargària de la paraula
private

   MAX: Integer := 50;
   type v_Paraula is array (1..MAX) of character;

   type Paraula is record
      v_p: v_Paraula;   --Vector de paraules.
      n: integer;	-- Comptador de caràcters de la paraula.
   end record;

   Paraula_Llarga: exception;

end d_Paraula;
