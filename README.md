## Instalación

1. **Clonar el Repositorio:**
   ```bash
   git clone https://tu-repositorio.git
   ```

2. **Compilar el Proyecto:**
   ```bash
   cd tu-repositorio
   make
   ```

3. **Configuración de Canciones:**
   - Coloca tus archivos de canciones en la carpeta `pooleProgram/data`. Crea una carpeta específica para organizar tus archivos.
## Uso

1. **Iniciar Discovery:**
   ```bash
   ./discovery (Nombre_configuracion)
   ```

2. **Iniciar Poole:**
   ```bash
   ./poole (Nombre_configuracion)
   ```

3. **Iniciar Bowman:**
   ```bash
   ./bowman (Nombre_configuracion)
   ```

4. **Conectar a Poole:**
   - En Bowman, utiliza el siguiente comando para conectarte a Poole:
     ```bash
     connect
     ```

5. **Utilizar las Funciones Disponibles:**
   - Listar Canciones:
     ```bash
     list song
     ```

   - Listar Playlists:
     ```bash
     list playlist
     ```

   - Descargar Canción:
     ```bash
     download (song).mp3
     ```

   - Descargar Playlist:
     ```bash
     download (Playlist)
     ```

   - Verificar Descargas:
     ```bash
     check downloads
     ```

   - Limpiar Descargas:
     ```bash
     clear downloads
     ```

   - Cerrar Sesión:
     ```bash
     logout
     ```
    
Esta adición indica claramente dónde encontrar las descargas en la carpeta `bowmanProgram/data`. ¡Espero que sea útil!
## Importante
Para poner los archivos de descarga/configuracion hay que pasar-lo con fileZilla o algun programa similar, ya que en formato windows puede provocar problemas 