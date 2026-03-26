<h2>Running this project</h2>
<h3>Launching backend</h3>
<ul>
  <li>Open the backend folder as a project in CLion (or any other C++ IDE).</li>
  <li>Reload the CMake project. This should generate the <code>cmake-build-debug</code> folder in the backend folder.</li>
  <li>Create a run configuration. The target and executable should be the <code>backend</code> project. Set the working directory to be <code>$ProjectFileDir$</code>.</li>
  <li>Build and run the project. The backend should now be live.</li>
  <li>To test the backend by itself (without using the frontend), launch the backend and navigate to <code>localhost:8080/search?word=</code> in your browser. Add a word at the end of the link to search for it. For example, <code>localhost:8080/search?word=data</code> would return the definition for the word "data".</li>
</ul>

<h3>Launching frontend</h3>
<ul>
  <li>CD into the frontend folder /frontend</li>
  <li>Make sure your node.js and npm are installed and up to date.</li>
  <li>Run npm install to install all packages needed</li>
  <li>Open localhost:3000</li>
</ul>
