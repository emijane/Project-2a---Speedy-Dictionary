<h2>Running this project</h2>

<h3>Launching backend</h3>
- Open the backend folder as a project in CLion (or any other C++ IDE).
- Reload the CMake project. This should generate the `cmake-build-debug` folder in the backend folder.
- Create a run configuration. The target and executable should be the `backend` project. Set the working directory to be `$ProjectFileDir$`.
- Build and run the project. The backend should now be live.
- To test the backend by itself (without using the frontend), launch the backend and navigate to `localhost:8080/search?word=` in your browser. Add a word at the end of the link to search for it. For example, `localhost:8080/search?word=data` would return the definition for the word "data".

<h3>Launching frontend</h3>
