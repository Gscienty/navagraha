import thunkMiddleware from 'redux-thunk';
import namespace from './reducers/namespace';
import systemInfo from './reducers/system_info';
import repo from './reducers/repo';
import func from './reducers/func';
import { combineReducers, createStore, applyMiddleware } from 'redux';

const rootReducer = combineReducers({
    namespace,
    systemInfo,
    repo,
    func
});

export default createStore(rootReducer, applyMiddleware(thunkMiddleware));
