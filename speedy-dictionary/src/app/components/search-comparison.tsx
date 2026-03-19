import React from 'react';

export const SearchComparison: React.FC = () => {
    return (
        <div className='max-w-3xl mt-10 pl-10'>
            <h3 className="text-2xl font-semibold text-black">
                Performance Comparison
            </h3>

            <div className="text-lg text-black mt-3">
                <p className='font-medium'>
                    Dataset: <span className="text-black/70 font-normal">1,000,000 English words + definitions</span>
                </p>
                <p className='font-medium'>
                    Structures Compared: <span className="text-black/70 font-normal">Red-Black Trees vs B-Trees</span>
                </p>
                <p className='font-medium'>
                    Time Complexity: <span className="text-black/70 font-normal">O(log n)</span>
                </p>
            </div>
        </div>
    );
};