import React from 'react';

export const SearchComparison: React.FC = () => {
    return (
        <div className='max-w-3xl mt-10'>
            <h3 className="text-3xl font-semibold text-black">
                Performance Comparison
            </h3>

            <div className="text-lg text-black mt-3 font-medium">
                <p>
                    Dataset: <span className="text-black/70">1,000,000 English words + definitions</span>
                </p>
                <p>
                    Structures Compared: <span className="text-black/70">Red-Black Trees vs B-Trees</span>
                </p>
                <p>
                    Time Complexity: <span className="text-black/70 font">O(log n)</span>
                </p>
            </div>
        </div>
    );
};