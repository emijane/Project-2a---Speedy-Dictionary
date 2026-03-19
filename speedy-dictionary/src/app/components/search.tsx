import React from 'react';

export const Search: React.FC = () => {
    return (
        <div className="my-10 pl-10">
            <div className="max-w-3xl">
                <input
                    type="text"
                    placeholder="Begin by searching for any word in the English Dictionary"
                    className="w-full rounded-2xl border-2 border-gray-200 px-4 py-3 text-sm text-black/70 font-medium outline-none focus:border-black placeholder-gray-600"
                />
            </div>
            
            <div className="mt-8">
                <h3 className="text-black text-2xl font-semibold">Word found: <span className='text-blue-600'>[Word will appear here]</span></h3>
                <p className="text-black/70 text-lg mt-1 font-medium">Definition: [Definition will appear here]</p>
            </div>
        </div>
    );
};