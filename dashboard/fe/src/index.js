import React from 'react';
import ReactDOM from 'react-dom';
import { HashRouter, Route, Switch } from 'react-router-dom';
import './index.css';
import App from './App';
import * as serviceWorker from './serviceWorker';

ReactDOM.render((
    <HashRouter>
        <Switch>
            <Route path="/" component={App} />
        </Switch>
    </HashRouter>
), document.getElementById('root'));

serviceWorker.unregister();
