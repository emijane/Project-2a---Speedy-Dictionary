import React from 'react';

export const Header: React.FC = () => {
    return (
        <div className='max-w-3xl mt-20 mb-10 pl-10'>
            <h1 className="bg-gradient-to-r from-blue-500 to-blue-700 bg-clip-text text-5xl font-bold leading-tight tracking-tight text-transparent">
                Fast English Dictionary & Word Definition Lookup
            </h1>
            <p className="text-black/80 mt-3 font-medium">Enter any English word to instantly retrieve its definition while our program measures how 
            quickly the data can be accessed. We compare two self-balancing data structures to 
            determine which retrieves definitions faster.</p>
        </div>
    );
};