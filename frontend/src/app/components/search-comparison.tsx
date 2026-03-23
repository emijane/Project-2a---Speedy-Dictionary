import React from 'react';

type SearchComparisonProps = {
    rbTime: number | null;
    bTime: number | null;
};

export const SearchComparison: React.FC<SearchComparisonProps> = ({ rbTime, bTime }) => {
    return (
        <div className="my-12 ml-20 not-first:max-w-4xl rounded-3xl border border-gray-200 bg-white p-8 shadow-sm">
            <div className="space-y-2">
                <p className="text-sm font-semibold uppercase tracking-wide text-blue-600">
                    Analysis
                </p>

                <h3 className="text-3xl font-bold text-black">
                    Performance Comparison
                </h3>

                <p className="max-w-2xl text-base leading-relaxed text-gray-600">
                    A quick comparison of how Red-Black Trees and B-Trees perform when searching
                    through a large English dictionary dataset.
                </p>
            </div>

            <div className="mt-6 grid gap-4 sm:grid-cols-3">
                <div className="rounded-2xl bg-gray-50 p-5">
                    <p className="text-sm font-medium text-gray-500">
                        Dataset
                    </p>
                    <p className="mt-2 text-lg font-semibold text-black">
                        1,000,000 English words + definitions
                    </p>
                </div>

                <div className="rounded-2xl bg-gray-50 p-5">
                    <p className="text-sm font-medium text-gray-500">
                        Structures Compared
                    </p>
                    <p className="mt-2 text-lg font-semibold text-black">
                        Red-Black Trees vs B-Trees
                    </p>
                </div>

                <div className="rounded-2xl bg-gray-50 p-5">
                    <p className="text-sm font-medium text-gray-500">
                        Time Complexity
                    </p>
                    <p className="mt-2 text-lg font-semibold text-black">
                        O(log n)
                    </p>
                </div>
            </div>

            <div className="mt-3 space-y-2 text-base text-gray-700">
                <p>
                    Red-Black Tree Time:{" "}
                    <span className="font-semibold text-black">
                        {rbTime !== null ? `${rbTime.toFixed(2)} microseconds` : "No search yet"}
                    </span>
                </p>

                <p>
                    B-Tree Time:{" "}
                    <span className="font-semibold text-black">
                        {bTime !== null ? `${bTime.toFixed(2)} microseconds` : "No search yet"}
                    </span>
                </p>
            </div>
        </div>
    );
};