with d_paraula,d_llistaparaules; use d_paraula,d_llistaparaules;
with ada.text_io, ada.command_line; use ada.text_io, ada.command_line;
procedure Programa is
   a: d_paraula.Paraula;
   l: d_Llistaparaules.llistaparaules;
   c: character;
   F: File_Type;
begin

   open(F, in_file, argument(1)&".txt");

   while (quedenParaules(F)) loop
      d_paraula.get(a, F);
      Posa(l,a);
   end loop;
   Escriu(l, Ascendent);
   new_line;
   Escriu(l, Descendent);
   new_line; new_line;
   Ordena(l);
   new_line;
   Escriu(l, Ascendent);
   new_line; new_line;
   Escriu(l, Descendent);
   get_immediate(c);
   close(F);


   end Programa;
