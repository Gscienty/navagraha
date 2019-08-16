import React from 'react';
import ReactDOM from 'react-dom';
import { Provider } from 'react-redux';
import { HashRouter, Route, Switch } from 'react-router-dom';
import './index.css';
import App from './App';
import * as serviceWorker from './serviceWorker';
import store from './reducer';
import 'antd/dist/antd.css';

ReactDOM.render((
    <Provider store={store}>
        <HashRouter>
            <Switch>
                <Route path="/" component={App} />
            </Switch>
        </HashRouter>
    </Provider>
), document.getElementById('root'));

serviceWorker.unregister();
