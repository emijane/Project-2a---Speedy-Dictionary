<h1>Speedy Dictionary</h1>
<h2>High-performance dictionary search application comparing Red-Black Trees and B-Trees, featuring a C++ backend and a modern Next.js frontend with real-time performance metrics.</h2>

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
  <li>Navigate to the frontend directory:
    <pre><code>cd frontend</code></pre>
  </li>
  <li>Ensure Node.js and npm are installed and up to date.</li>
  <li>Install dependencies:
    <pre><code>npm install</code></pre>
  </li>
  <li>Start the development server:
    <pre><code>npm run dev</code></pre>
  </li>
  <li>Open your browser and go to:
    <pre><code>http://localhost:3000</code></pre>
  </li>
</ul>
