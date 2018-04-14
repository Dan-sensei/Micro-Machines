# Micro Machines


### Videojuego desarrollado en C++ con SFML


Dado que nuestro grupo emplea Manjaro, el cual es una distribución de ArchLinux, la configuración de Netbeans es ligeramente distinta a la de Ubuntu:

```
Project Properties_________________________________________________________
			|
			|-- C++ Compiler
			|	|--------- Include Directories: /usr/include/SFML
			|
			|
			|-- Linker
				|--------- Additional Library Directories: /usr/lib
				|--------- Libraries > Add Librarie File...
								|----- libsfml-window.so
								|----- libsfml-audio.so
								|----- libsfml-graphics.so
								|----- libsfml-system.so

```

## Controles

####	JUGADOR 1:
```
	                        .---.                        
	                       /. ./|                        
	                    .-'-. ' |                        
	                   /___/ \: |                        
	                .-'.. '   ' .                        
	               /___/ \:     '                        
	               .   \  ' .\                           
	                \   \   ' \ |                        
	                 \   \  |--"                         
	                  \   \ |                      ,---, 
	                   '---"                     ,---.'| 
	                       .--.--.               |   | : 
	   ,--.--.            /  /    '              |   | | 
	  /       \          |  :  /`./            ,--.__| | 
	 .--.  .-. |         |  :  ;_             /   ,'   | 
	  \__\/: . .          \  \    `.         .   '  /  | 
	  ," .--.; |           `----.   \        '   ; |:  | 
	 /  /  ,.  |          /  /`--'  /        |   | '/  ' 
	;  :   .'   \        '--'.     /         |   :    :| 
	|  ,     .-./          `--'---'           \   \  /   
	 `--`---'                                  `----'    
                                                     
```

####	JUGADOR 2:
```

                                 .
                               .:;:.
                             .:;;;;;:.
                               ;;;;;
                               ;;;;;
                               ;;;;;
                               ;;;;;
                               : ;;;
                                 ;:;
                               . :.;
                                 . :
                               .   .

                                  .

                                 .
                                   .
                               . ;.
                                .;
                                 ;;.
                               ;.;;
                               ;;;;.
                               ;;;;;
       .                       ;;;;;                      .
     .;;............ ..        ;;;;;       .. ............;;.
   .;;;;::::::::::::..         ;;;;;        ..::::::::::::;;;;.
    ':;;:::::::::::: . .     ..;;;;;..    . . ::::::::::::;;:'
      ':                      ':::::'                     :'
                                ':`

```

###	Salir:               
	                 
		    ,----..      
		   /   /   \     
		  /   .     :    
		 .   /   ;.  \   
		.   ;   /  ` ;   
		;   |  ; \ ; |   
		|   :  | ; | '   
		.   |  ' ' ' :   
		'   ;  \; /  |   
		 \   \  ',  . \  
		  ;   :      ; | 
		   \   \ .'`--"  
		    `---`        
                 



## Parámetros

	Nº JUGADORES: main.cpp -> Línea 20: Primer parámetro
	  Nº VUELTAS: main.cpp -> Línea 20: Segundo parámetro

	int main(int argc, char** argv) {
        Game game       (1, 2);			// 1 jugador,   2 Vueltas
        game.go();
	}


	int main(int argc, char** argv) {
        Game game       (2, 800);			// 2 jugadores, 800 Vueltas
        game.go();
	}



## Mejoras realizadas

	- Interpolación -> Se puede ajustar desde el #define TICK de Game.cpp (Línea 20)
	- 2 Jugadores 	-> Pantalla dividida
	- SAT  		-> Separation Axis Theorem para las colisiones
	- Turbo
	- Salto		-> Se desactivan las colisiones entre coches en el aire
	- Animaciones	-> Todos los turbos se representan mediante un gif animado
	- Sonidos	-> Música de fondo, victoria y derrota, así como un efecto al coger el turbo


### Autor
Danny Gabriel Rivera Solórzano
