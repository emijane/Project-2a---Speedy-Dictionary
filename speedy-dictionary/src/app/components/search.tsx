import React from 'react';

export const Search: React.FC = () => {
    return (
        <div className="max-w-4xl space-y-6 py-10 px-20">
            <h2 className="text-3xl font-bold text-black">
                Let&apos;s find your definition
            </h2>

            <input
                type="text"
                placeholder="Begin by searching for any word in the English Dictionary"
                className="w-full rounded-2xl border border-gray-300 bg-white px-5 py-4 text-base text-gray-700 outline-none transition focus:border-blue-500"
            />

            <div className="rounded-2xl bg-gray-50">
                <h3 className="text-2xl font-bold text-black">
                    Word found: <span className="text-blue-600">example</span>
                </h3>

                <p className="text-lg leading-relaxed text-gray-700">
                    The definition will appear here after the user searches for a word.
                </p>
            </div>
        </div>
    );
};