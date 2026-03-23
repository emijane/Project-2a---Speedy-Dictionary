"use client";

import React, { useState } from "react";
import { Header } from "./components/header";
import { Search } from "./components/search";
import { SearchComparison } from "./components/search-comparison";
import { BTreeFact } from "./components/b-tree-fact";
import type { SearchResponse } from "./lib/api";

export default function Home() {
  const [result, setResult] = useState<SearchResponse | null>(null);

  return (
    <div className="flex flex-col flex-1 bg-zinc-50 font-sans tracking-tight lg:px-50 p-10">
        <div className="border-l-2 border-gray-100">
          <span className="text-black font-bold text-xl pl-20">Speedy Dictionary</span>
          <Header />
          <hr className="border-t border-2 border-gray-100" />
          <Search result={result} setResult={setResult} />
          <hr className="border-t border-2 border-gray-100" />
          <SearchComparison
              rbTime={result ? result.rbTime : null}
              bTime={result ? result.bTime : null}
          />
          <hr className="border-t border-2 border-gray-100" />
          <BTreeFact />
          <hr className="border-t border-2 border-gray-100" />
        </div>
        <p className="text-black/70 ml-20 mt-12">Made with love by Russell MacGregor, Ryan Cecil, and Emma DeNunzio.</p>
    </div>
  );
}
