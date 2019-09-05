import {
    NODE_LIST_SET,
    NODE_LIST_UNSET,
    NODE_LIST_RECEIVE_POST,
    NODE_LIST_REQUEST_POST
} from '../actions/node';

const initState = {
    state: NODE_LIST_UNSET,
    nodes: []
};

export default function nodeReduce(state = initState, action) {

    switch (action.type) {

        case NODE_LIST_RECEIVE_POST:
            return Object.assign({}, state, {
            state: NODE_LIST_SET,
            nodes: action.nodes
        });

        case NODE_LIST_REQUEST_POST:
            return state;

        default:
            return state;
    }
};
