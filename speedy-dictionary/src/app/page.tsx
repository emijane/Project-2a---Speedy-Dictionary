import React from "react";
import { Header } from "./components/header";
import { Search } from "./components/search";
import { SearchComparison } from "./components/search-comparison";
import { SearchComparisonCards } from "./components/search-comparison-cards";
import { BTreeFact } from "./components/b-tree-fact";

export default function Home() {
  return (
    <div className="flex flex-col flex-1 bg-zinc-50 font-sans tracking-tight lg:px-50 p-10">
        <div className="border-l-2 border-gray-100">
          <span className="text-black font-bold text-xl pl-20">Speedy Dictionary</span>
          <Header />
          <hr className="border-t border-2 border-gray-100" />
          <Search />
          <hr className="border-t border-2 border-gray-100" />
          <SearchComparison />
          <SearchComparisonCards />
          <hr className="border-t border-2 border-gray-100" />
          <BTreeFact />
        </div>
    </div>
  );
}
