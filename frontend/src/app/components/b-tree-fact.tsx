import React from 'react';

export const BTreeFact: React.FC = () => {
    return (
        <div className=" max-w-3xl mt-10 pl-20">
            <h3 className="text-black text-2xl font-semibold">Why is the B-Tree faster?</h3>
            <p className="text-black/80 mt-2 font-medium">Red-Black Trees store one key per node, creating a deeper tree (~log₂(n) levels).
                B-Trees store many keys per node, reducing the overall tree height log_b(n) levels.</p>
        </div>
    );
};