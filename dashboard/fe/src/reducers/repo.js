import {
    REPO_REQUEST_POST,
    REPO_RECEIVE_POST,
    REPO_UNSET,
    REPO_SET
} from '../actions/repo';

const initState = {
    state: REPO_UNSET,
    repo: []
};

export default function repoReduce(state = initState, action) {
    
    switch (action.type) {

        case REPO_RECEIVE_POST:
            return Object.assign({}, state, {
                state: REPO_SET,
                repo: action.repo
            });

        case REPO_REQUEST_POST:
            return Object.assign({}, state, {
                state: REPO_UNSET,
            });

        default:
            return state;
    }
}

