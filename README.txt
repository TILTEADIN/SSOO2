
Hola Javier, asumo que habrás leído la ficha de autoevaluación y te preguntarás porque teniendo tantas casillas marcadas
me he autoevaluado con un 4.  Mi codigo tiene muchas horas de trabajo, de investigar y reaprender muchos conceptos que había olvidado
en los dos años que han pasado desde la última vez que programé en C.
Mis Procesos A, B, C y D cuando funcionan de forma atómica lo hacen correctamente, están estructurados con las variables con los nombres como 
se exigen por convención, así como con cabeceras y comentarios explicativos, en mi opinión es buen código.

El problema llega con el Manager, en el que he sido incapaz de solucionar un error en el que la ejecución se queda colgada.
Mi log registra que el proceso A termina y luego se cuelga hasta que hago un control+C, he debugueado el codigo y no he sabido encontrar que lo provoca,
a pesar de que efectivamente el proceso A termina de forma correcta, no se crean las carpetas de los estudiantes cuando ejecutado de forma atómica si lo hace.
Me gustaría una tutoría en la que me ayudaras a comprender que no he hecho bien, ya que me he sentido bastante impotente.
______________

La estructura de archivos es la siguiente:
    bin --> guarda el codigo ya compilado
    obj --> los archivos .o
    src --> el código fuente
    MODELOSEXAMEN --> los modelos A B y C 

Para compilar escribir en la terminal desde el directorio P1: make 
Para ejecutar escribir en la terminal desde el directorio P1: make run