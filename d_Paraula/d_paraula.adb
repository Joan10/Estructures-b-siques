with ada.text_io; use ada.text_io;
with ada.integer_text_io; use ada.integer_text_IO;
package body d_Paraula is
   c: character := ' ';
   fi_linia: boolean := true;

   procedure Get(P: out Paraula; F: in File_Type) is
   begin
      P.n := 0;
      while not(c /= ' ' and c /= '.' and c /= ',' and c /= '!' and c /= '?') and not(end_of_file(F)) loop
         get(F,c);
      end loop;
      fi_linia:=end_of_file(F);
      while c /= ' ' and c /= '.' and c /= ',' and c /= '!' and c /= '?' and not(fi_linia) loop
         if P.n = 50 then raise Paraula_Llarga; end if;
         fi_linia:=end_of_file(F);
	 P.n:=P.n+1;
         P.v_p(P.n) := c;
         if not(fi_linia) then get(F,c); end if;
      end loop;

      for i in P.n+1..MAX loop --omplim els espais que sobren amb el valor anterior a 'a'
      	P.v_p(i):=character'val(32);
      end loop;


   exception
         when END_ERROR => Put("Format de fitxer erroni!");
   end get;


   procedure Put(P: in Paraula) is
      i : integer := 1;
   begin
     -- put(P.n);
      while i <= P.n loop
         put(P.v_p(i));
         i := i+1;
      end loop;
      Put(' ');
   end Put;

   function quedenParaules(F: in file_type) return boolean is
   begin
      	while not(c /= ' ' and c /= '.' and c /= ',' and c /= '!' and c /= '?') and not(end_of_file(F)) loop
          get(F,c);
      	end loop;
	return not(end_of_file(F));
   end quedenParaules;

   function llargaria(P: in Paraula) return integer is --Retorna el nombre de caràcters d'una paraula
   begin
      return P.n;
   end llargaria;

   function charPos(P: in Paraula; Pos: in integer) return character is --retorna el caràcter de la paraula que cau a la posició passada.
   begin
      return P.v_p(Pos);
   end charPos;


end d_Paraula;
