import React from 'react';

export const SearchComparisonCards: React.FC = () => {
    return (
        <div className="mt-5 grid gap-6 md:grid-cols-2 max-w-3xl mb-10">
            <div className="rounded-[28px] bg-gray-100 p-8 shadow-sm">
                <h2 className="mb-3 text-xl font-semibold text-black">
                    Slower: Red-Black Tree
                </h2>

                <div className="text-lg text-black font-medium">
                    <p>
                        Levels searched: <span className="text-gray-600">20</span>
                    </p>
                    <p>
                        Key comparisons: <span className="text-gray-600">20</span>
                    </p>
                    <p>
                        Time: <span className="text-red-500">0.1 ms (0.0001 s)</span>
                    </p>
                    <p>
                        Algorithm: <span className="text-gray-600">Balanced BST search</span>
                    </p>
                </div>
            </div>

            <div className="rounded-[28px] bg-gray-100 p-8 shadow-sm">
                <h2 className="mb-3 text-xl font-semibold text-black">
                    Faster: B-Tree
                </h2>

                <div className="text-lg text-black font-medium">
                    <p>
                        Levels searched: <span className="text-gray-600">4</span>
                    </p>
                    <p>
                        Key comparisons: <span className="text-gray-600">6</span>
                    </p>
                    <p>
                        Time: <span className="text-green-600">0.01 ms (0.00001 s)</span>
                    </p>
                    <p>
                        Algorithm: <span className="text-gray-600">multi-key node search</span>
                    </p>
                </div>
            </div>
        </div>
    );
};