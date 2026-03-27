"use client";

import React, { useState } from "react";
import { searchWord, type SearchResponse } from "../lib/api";

type SearchProps = {
    result: SearchResponse | null;
    setResult: React.Dispatch<React.SetStateAction<SearchResponse | null>>;
};

// This component allows users to search for a word and displays the 
// definition along with performance metrics.
export const Search: React.FC<SearchProps> = ({ result, setResult }) => {
    // State variables to manage the search input, results, loading state, and errors
    const [word, setWord] = useState("");
    const [loading, setLoading] = useState(false);
    const [error, setError] = useState("");

    // Function to handle the search action when the user clicks 
    // the search button or presses Enter
    const handleSearch = async () => {
        // Prevent searching for empty or whitespace-only input
        if (!word.trim()) {
            return;
        }

        // Reset state before starting a new search
        setLoading(true);
        setError("");

        // Attempt to fetch search results from the backend API
        try {
            // Call the searchWord function to get the definition and time
            const data = await searchWord(word);
            setResult(data);

        // Handle any errors that occur during the fetch operation
        } catch (err) {
            console.error("Search failed:", err);
            setError("Could not connect to backend.");
            setResult(null);
        }

        // Set loading to false after the search operation is complete
        setLoading(false);
    };

    // Function to handle the Enter key press in the input field
    const handleKeyDown = async (e: React.KeyboardEvent<HTMLInputElement>) => {
        if (e.key === "Enter") {
            await handleSearch();
        }
    };

    // Calculate amount of definitions returned
    const definitionCount = result ? result.definition.split("\n").length : 0;

    // Render the search input, button, and results based on the current state
    return (
        <div className="max-w-4xl space-y-6 px-20 py-10">
            <h2 className="text-3xl font-bold text-black">
                Let&apos;s find your definition
            </h2>

            <div className="flex gap-3">
                <input
                    type="text"
                    value={word}
                    onChange={(e) => setWord(e.target.value)}
                    onKeyDown={handleKeyDown}
                    placeholder="Begin by searching for any word in the English Dictionary"
                    className="w-full rounded-2xl border border-gray-300 bg-white px-5 py-4 text-base text-gray-700 outline-none transition focus:border-blue-500"
                />

                <button
                    onClick={handleSearch}
                    className="rounded-2xl bg-blue-600 px-6 py-4 text-base font-semibold text-white transition hover:bg-blue-700"
                >
                    Search
                </button>
            </div>
            
            {loading && (
                <div className="rounded-2xl bg-gray-50 p-6">
                    <p className="text-lg text-gray-700">Searching...</p>
                </div>
            )}

            {error && (
                <div className="rounded-2xl bg-gray-50 p-6">
                    <p className="text-lg text-red-500">{error}</p>
                </div>
            )}

            {!loading && !error && (
                <div className="rounded-2xl bg-gray-50">
                    <h3 className="text-2xl font-bold text-black">
                        Word found:{" "}
                        <span className="text-blue-600">
                            {result ? result.word : "example"}
                        </span>
                    </h3>

                    <ul className="text-lg leading-relaxed text-gray-700">
                        {definitionCount > 1 && (
                            <p className="text-sm font-medium mt-1 mb-3 text-gray-500">
                                {definitionCount} definitions found:
                            </p>
                        )}
                        {result ? (
                            result.definition.split("\n").map((definition, index) => (
                                <li key={index} className="list-disc list-inside">
                                    {definition}
                                </li>
                            ))
                        ) : (
                            <li className="list-disc list-inside">
                                The definition will appear here after the user searches for a word.
                            </li>
                        )}
                    </ul>
                </div>
            )}
        </div>
    );
};