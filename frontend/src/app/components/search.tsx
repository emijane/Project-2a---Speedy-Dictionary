"use client";

import React, { useState } from "react";
import { searchWord, type SearchResponse } from "../lib/api";

export const Search: React.FC = () => {
    const [word, setWord] = useState("");
    const [result, setResult] = useState<SearchResponse | null>(null);
    const [loading, setLoading] = useState(false);
    const [error, setError] = useState("");

    const handleSearch = async () => {
        if (!word.trim()) {
            return;
        }

        setLoading(true);
        setError("");

        try {
            const data = await searchWord(word);
            setResult(data);
        } catch (err) {
            console.error("Search failed:", err);
            setError("Could not connect to backend.");
            setResult(null);
        }

        setLoading(false);
    };

    const handleKeyDown = async (e: React.KeyboardEvent<HTMLInputElement>) => {
        if (e.key === "Enter") {
            await handleSearch();
        }
    };

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
                <div className="rounded-2xl bg-gray-50 p-6">
                    <h3 className="text-2xl font-bold text-black">
                        Word found:{" "}
                        <span className="text-blue-600">
                            {result ? result.word : "example"}
                        </span>
                    </h3>

                    <p className="mt-3 text-lg leading-relaxed text-gray-700 whitespace-pre-line">
                        {result
                            ? result.definition
                            : "The definition will appear here after the user searches for a word."}
                    </p>

                    {result && (
                        <div className="mt-4 space-y-2 text-base text-gray-600">
                            <p>
                                Red-Black Tree Time:{" "}
                                <span className="font-semibold">{result.rbTime} μs</span>
                            </p>
                            <p>
                                B-Tree Time:{" "}
                                <span className="font-semibold">{result.bTime} μs</span>
                            </p>
                        </div>
                    )}
                </div>
            )}
        </div>
    );
};