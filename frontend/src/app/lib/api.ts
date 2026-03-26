// api.ts
// This module defines the API for searching words in the dictionary. It includes
// the SearchResponse type and the searchWord function that interacts with the backend API.
export type SearchResponse = {
    word: string;
    definition: string;
    rbTime: number;
    bTime: number;
};

// Base URL for the backend API.
const API_BASE_URL = "http://localhost:8080";

// Function to search for a word using the backend API. It takes a word as input and returns
// a Promise that resolves to a SearchResponse object containing the word, its definition,
// and the time taken for both Red-Black Tree and B-Tree searches.
export async function searchWord(word: string): Promise<SearchResponse> {
    const response = await fetch(
        `${API_BASE_URL}/search?word=${encodeURIComponent(word)}`
    );

    if (!response.ok) {
        throw new Error("Failed to fetch search results");
    }

    return response.json();
}