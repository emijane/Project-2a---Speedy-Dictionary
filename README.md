<h1>Speedy Dictionary</h1>
<p>High-performance dictionary search application comparing Red-Black Trees and B-Trees, featuring a C++ backend and a modern Next.js frontend with real-time performance metrics.</p>

<h1>Starting the Backend Server</h1>

<p>
    The backend can be run in <strong>Debug</strong> or <strong>Release</strong> mode.
</p>

<ul>
    <li><strong>Debug:</strong> for development and fixing issues</li>
    <li><strong>Release:</strong> for accurate performance testing</li>
</ul>

<h2>Prerequisites</h2>

<ul>
    <li>CMake installed</li>
    <li>A C++ compiler installed</li>
    <li><code>dictionary.csv</code> inside the <code>backend</code> folder</li>
</ul>

<pre><code>backend/
├── CMakeLists.txt
├── main.cpp
├── dictionary.csv
├── rb_tree/
├── b_tree/
├── csv_parsing/
</code></pre>

<h2>CSV Path</h2>

<p>
    Since the executable runs inside a build folder, use:
</p>

<pre><code>load_csv(&amp;rb_tree_inst, &amp;b_tree_inst, "../../dictionary.csv");</code></pre>

<h1>Build and Run (Debug)</h1>

<pre><code>cd backend
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
cmake --build . --config Debug
cd Debug
.\backend.exe
</code></pre>

<h1>Build and Run (Release)</h1>

<pre><code>cd backend
mkdir cmake-build-release
cd cmake-build-release
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cd Release
.\backend.exe
</code></pre>

<h1>Rebuilding</h1>

<p>If something breaks, delete the build folder and rebuild:</p>

<pre><code>cd backend
Remove-Item -Recurse -Force cmake-build-debug
# or cmake-build-release

mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
cmake --build . --config Debug
</code></pre>

<h1>Running the Full Project</h1>

<p>Run both servers at the same time:</p>

<ul>
    <li>Terminal 1: backend (Debug or Release) -> localhost:8080 once running</li>
    <li>Terminal 2: frontend -> localhost:3000 once running</li>
</ul>

<pre><code>cd frontend
npm install
npm run dev
</code></pre>

<h1>Notes</h1>

<ul>
    <li>The backend terminal staying open with no output usually means it is running</li>
    <li>Use <strong>Release mode</strong> for performance comparisons</li>
    <li>If search fails, make sure the backend server is running</li>
</ul>