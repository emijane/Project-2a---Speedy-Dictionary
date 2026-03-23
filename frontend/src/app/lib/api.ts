export type SearchResponse = {
    word: string;
    definition: string;
    rbTime: number;
    bTime: number;
};

const API_BASE_URL = "http://localhost:8080";

export async function searchWord(word: string): Promise<SearchResponse> {
    const response = await fetch(
        `${API_BASE_URL}/search?word=${encodeURIComponent(word)}`
    );

    if (!response.ok) {
        throw new Error("Failed to fetch search results");
    }

    return response.json();
}